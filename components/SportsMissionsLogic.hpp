#include <generated/SportsMissions_config.generated.h>

class SportsMissionsLogic {
private:
	SportsMissionsConfig _config;
	SportsMissionsBalance _balance;
	IMatch3* _match3;

	SportsMissionsLogic() = default;

	void SetConfig(SportsMissionsConfig&& config) { _config = std::move(config); };
	void SetBalance(SportsMissionsBalance&& balance) { _balance = std::move(_balance); };
	void SetMatch3(IMatch3* match3) { _match3 = match3; };

	// Logic...

public:
	Ptr<SportsMissionsLogic> Instance(SportsMissionsConfig&& config, SportsMissionsBalance&& balance, IMatch3* match3)
	{
		auto Instance = Core::Make<SportsMissionsLogic>();
		Instance.SetConfig(config);
		Instance.SetBalance(balance);
		Instance.SetMatch3(match3);
		return Instance;
	}
}