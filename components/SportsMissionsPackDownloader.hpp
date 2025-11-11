#include <SportsMissions_config.generated.h>

class SportsMissionsPackDownloader {
private:
	ResourcePackDownloadConfig _config;
	IPlayerInfo* _playerInfo;

	SportsMissionsPackDownloader() = default;

	void SetConfig(SportsMissionsConfig&& config) { _config = std::move(config); };
	void SetPlayerInfo(IPlayerInfo* playerInfo) { _playerInfo = playerInfo; };

	// Logic...

public:
	Ptr<SportsMissionsPackDownloader> Instance(SportsMissionsConfig&& config, IPlayerInfo* playerInfo)
	{
		auto Instance = Core::Make<SportsMissionsPackDownloader>();
		Instance.SetConfig(config);
		Instance.SetPlayerInfo(playerInfo);
		return Instance;
	}
}