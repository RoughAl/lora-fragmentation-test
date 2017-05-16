#include "dot_util.h"
#include "RadioEvent.h"

#if ACTIVE_EXAMPLE == OTA_EXAMPLE

static uint8_t network_id[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xF0, 0x00, 0x3D, 0xAA };
static uint8_t network_key[] = { 0x96, 0xCD, 0xBD, 0xE6, 0x28, 0x03, 0x87, 0xED, 0x1E, 0x24, 0xA0, 0x21, 0x8C, 0x0B, 0xBB, 0x9C };
static bool public_network = true;
static uint8_t ack = 0;

static bool deep_sleep = false;

mDot* dot = NULL;

Serial pc(USBTX, USBRX);

AnalogIn lux(XBEE_AD0);

int main() {
    // Custom event handler for automatically displaying RX data
    RadioEvent events;

    pc.baud(115200);

    mts::MTSLog::setLogLevel(mts::MTSLog::TRACE_LEVEL);

    dot = mDot::getInstance();

    // attach the custom events handler
    dot->setEvents(&events);

    logInfo("mbed-os library version: %d", MBED_LIBRARY_VERSION);

    // start from a well-known state
    logInfo("defaulting Dot configuration");
    dot->resetConfig();
    dot->resetNetworkSession();

    // make sure library logging is turned on
    dot->setLogLevel(mts::MTSLog::INFO_LEVEL);

    // update configuration if necessary
    if (dot->getJoinMode() != mDot::OTA) {
        logInfo("changing network join mode to OTA");
        if (dot->setJoinMode(mDot::OTA) != mDot::MDOT_OK) {
            logError("failed to set network join mode to OTA");
        }
    }

    // in OTA and AUTO_OTA join modes, the credentials can be passed to the library as a name and passphrase or an ID and KEY
    // only one method or the other should be used!
    // network ID = crc64(network name)
    // network KEY = cmac(network passphrase)
    // update_ota_config_name_phrase(network_name, network_passphrase, frequency_sub_band, public_network, ack);
    update_ota_config_id_key(network_id, network_key, frequency_sub_band, public_network, ack);

    // configure network link checks
    // network link checks are a good alternative to requiring the gateway to ACK every packet and should allow a single gateway to handle more Dots
    // check the link every count packets
    // declare the Dot disconnected after threshold failed link checks
    // for count = 3 and threshold = 5, the Dot will be considered disconnected after 15 missed packets in a row
    update_network_link_check_config(3, 5);

    // save changes to configuration
    logInfo("saving configuration");
    if (!dot->saveConfig()) {
        logError("failed to save configuration");
    }

    logInfo("changing network mode to class C");
    if (dot->setClass("C") != mDot::MDOT_OK) {
        logError("failed to set network mode to class C");
    }

    dot->setTxDataRate(mDot::SF_7);

    // display configuration
    display_config();

    dot->setTxDataRate(mDot::SF_7);

    while (true) {
        uint16_t light;
        std::vector<uint8_t> tx_data;

        dot->setRxDataRate(mDot::SF_7);

        logInfo("Rx freq: %d, dr=%d\n", dot->getRxFrequency(), dot->getRxDataRate());


        // join network if not joined
        if (!dot->getNetworkJoinStatus()) {
            join_network();
            logInfo("AFTER JOIN");
            display_config();
        }
        dot->setTxDataRate(mDot::SF_7);

#if defined(TARGET_XDOT_L151CC)
        // configure the ISL29011 sensor on the xDot-DK for continuous ambient light sampling, 16 bit conversion, and maximum range
        lux.setMode(ISL29011::ALS_CONT);
        lux.setResolution(ISL29011::ADC_16BIT);
        lux.setRange(ISL29011::RNG_64000);

        // get the latest light sample and send it to the gateway
        light = lux.getData();
        tx_data.push_back((light >> 8) & 0xFF);
        tx_data.push_back(light & 0xFF);
        logInfo("light: %lu [0x%04X]", light, light);
        send_data(tx_data);

        // put the LSL29011 ambient light sensor into a low power state
        lux.setMode(ISL29011::PWR_DOWN);
#else
        // get some dummy data and send it to the gateway
        light = lux.read_u16();
        tx_data.push_back((light >> 8) & 0xFF);
        tx_data.push_back(light & 0xFF);
        logInfo("light: %lu [0x%04X]", light, light);
        send_data(tx_data);
#endif

        // if going into deepsleep mode, save the session so we don't need to join again after waking up
        // not necessary if going into sleep mode since RAM is retained
        if (deep_sleep) {
            logInfo("saving network session to NVM");
            dot->saveNetworkSession();
        }

        // dot->openRxWindow(0);

        printf("Sleeping for 30s\n");
        wait_ms(30000);

        // ONLY ONE of the three functions below should be uncommented depending on the desired wakeup method
        //sleep_wake_rtc_only(deep_sleep);
        //sleep_wake_interrupt_only(deep_sleep);
        // sleep_wake_rtc_or_interrupt(deep_sleep);
    }

    return 0;
}

#endif
