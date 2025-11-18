#include <SportsMissions_config.generated.h>

class SportsMissionsPackDownloader {
private:
	ResourcePackDownloadConfig _config;

	SportsMissionsPackDownloader() = default;

	void SetConfig(SportsMissionsConfig&& config) { _config = std::move(config); };

	// Logic...

public:
	Ptr<SportsMissionsPackDownloader> Instance(SportsMissionsConfig&& config)
	{
		auto Instance = Core::Make<SportsMissionsPackDownloader>();
		Instance.SetConfig(config);
		return Instance;
	}
}