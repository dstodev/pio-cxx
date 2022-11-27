#ifndef PIO_CXX_CONSTANTS_HXX
#define PIO_CXX_CONSTANTS_HXX

constexpr auto LoopCycleTime = 10 /* seconds */;
constexpr auto TaskProcessingTime = 3 /* seconds */;
constexpr auto SerialBaudRate = 112'500 /* bits per second */;
constexpr auto UdpBroadcastPort = 58'400;
constexpr auto WaitForSerialDelay = 1 /* seconds */;
constexpr auto WaitForWiFiDelay = 7 /* seconds */;

constexpr auto SleepWakeupDelay = LoopCycleTime - TaskProcessingTime;
static_assert(SleepWakeupDelay >= 1, "Less than a second might not be worth sleeping for.");

constexpr auto WatchdogPanicTimeout = LoopCycleTime * 2;
static_assert(WatchdogPanicTimeout > LoopCycleTime, "WatchdogPanicTimeout must exceed LoopCycleTime.");
static_assert(WatchdogPanicTimeout > WaitForSerialDelay, "WatchdogPanicTimeout must exceed WaitForSerialDelay.");
static_assert(WatchdogPanicTimeout > WaitForWiFiDelay, "WatchdogPanicTimeout must exceed WaitForWiFiDelay.");

#endif  // PIO_CXX_CONSTANTS_HXX
