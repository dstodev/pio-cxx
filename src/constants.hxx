#ifndef PIO_CXX_CONSTANTS_HXX
#define PIO_CXX_CONSTANTS_HXX

constexpr auto SleepWakeupDelay = 10 /* seconds */;
static_assert(SleepWakeupDelay >= 1, "Less than a second might not be worth sleeping for.");

constexpr auto SerialBaudRate = 112'500 /* bits per second */;
constexpr auto UdpBroadcastPort = 58'400;
constexpr auto WaitForSerialDelay = 5 /* seconds */;
constexpr auto WaitForWiFiDelay = 15 /* seconds */;

constexpr auto WatchdogPanicTimeout = SleepWakeupDelay * 2;
static_assert(WatchdogPanicTimeout > SleepWakeupDelay, "WatchdogPanicTimeout must exceed LoopCycleTime.");
static_assert(WatchdogPanicTimeout > WaitForSerialDelay, "WatchdogPanicTimeout must exceed WaitForSerialDelay.");
static_assert(WatchdogPanicTimeout > WaitForWiFiDelay, "WatchdogPanicTimeout must exceed WaitForWiFiDelay.");

#endif  // PIO_CXX_CONSTANTS_HXX
