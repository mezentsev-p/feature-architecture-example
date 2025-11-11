#include <SportsMissions_config.generated.h>

class SportsMissionsScheduler {
private:
	ScheduleConfig _config;

	SportsMissionsScheduler() = default;

	void SetConfig(ScheduleConfig&& config) { _config = std::move(config); };

	// Logic...

public:
	Ptr<SportsMissionsScheduler> Instance(ScheduleConfig&& config)
	{
		auto Instance = Core::Make<SportsMissionsScheduler>();
		Instance.SetConfig(config);
		return Instance;
	}
}