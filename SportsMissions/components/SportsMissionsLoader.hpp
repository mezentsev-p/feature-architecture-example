#include <SportsMissions_config.generated.h>

class SportsMissions;

class SportsMissionsLoader {
private:
	LocalContextConfigVariables _configVariables;
	Ptr<SportsMissionsScheduler> _scheduler;
	Ptr<SportsMissionsPackDownloader> _packDownloader;
	WeakPtr<SportsMissions> _sportsMissions;
	Ptr<Condition> _launchCondition;

	SportsMissionsLoader() = default;

	void SetConfigVariabels(LocalContextConfigVariables& variables) { _configVariables = variables; };
	void SetScheduler(Ptr<SportsMissionsScheduler> scheduler) { _scheduler = scheduler; };
	void SetDownloader(Ptr<SportsMissionsPackDownloader> packDownloader) { _playerInfo = playerInfo; };
	void SetSportsMissions(Ptr<SportsMissions> & sportsMissions) { _sportsMissions = MakeWeak(sportsMissions); };
	
	void OnLoaded()
	{
		_sportsMissions->OnLoaded();
	}

	void Init()
	{
		_launchCondition = magic::MakeCondition(_configVariables.check_launch_requirements);
		_launchCondition.Subscribe([this](){ OnLoaded(); });
	}

public:
	Ptr<SportsMissionsLoader> Instance(LocalContextConfigVariables& variables, Ptr<SportsMissionsScheduler> scheduler, Ptr<SportsMissionsPackDownloader> packDownloader, Ptr<SportsMissions> & sportsMissions)
	{
		auto Instance = Core::Make<SportsMissionsLoader>();
		Instance.SetConfigVariabels(variables);
		Instance.SetScheduler(scheduler);
		Instance.SetDownloader(packDownloader);
		Instance.SetSportsMissions(sportsMissions);
		Instance->Init();
		return Instance;
	}
}