#ifndef PIO_CXX_CONSTANTS_HXX
#define PIO_CXX_CONSTANTS_HXX

constexpr auto SerialBaudRate = 112'500 /* bits per second */;
constexpr auto SleepWakeupDelay = 4 /* seconds */;
constexpr auto UdpBroadcastPort = 58'400;
constexpr auto WaitForSerialDelay = 10'000 /* ms */;
constexpr auto WaitForWiFiDelay = 10'000 /* ms */;
constexpr auto WakeupExtraProcessingTime = 1 /* seconds */;
constexpr auto WatchdogPanicTimeout = 20 /* seconds */;

#endif  // PIO_CXX_CONSTANTS_HXX
