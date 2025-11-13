#include <generated/SportsMissions_config.generated.h>

class SportsMissionsLogic {
private:
	SportsMissionsConfig _config;
	SportsMissionsBalance _balance;
	IMatch3* _match3;
	IPlayerInfo * _playerInfo;

	SportsMissionsLogic() = default;

	void SetConfig(SportsMissionsConfig& config) { _config = config; };
	void SetBalance(SportsMissionsBalance& balance) { _balance = _balance; };
	void SetMatch3(IMatch3* match3) { _match3 = match3; };
	void SetPlayerInfo(IPlayerInfo* playerInfo) { _playerInfo = playerInfo; };

public:
	void StartMission()
	{
		// Do something
	}

	// Logic...

public:
	Ptr<SportsMissionsLogic> Instance(SportsMissionsConfig&& config, SportsMissionsBalance&& balance, IMatch3* match3, IPlayerInfo* playerInfo)
	{
		auto Instance = Core::Make<SportsMissionsLogic>();
		Instance.SetConfig(config);
		Instance.SetBalance(balance);
		Instance.SetMatch3(match3);
		Instance.SetPlayerInfo(playerInfo);
		return Instance;
	}
}