#include <generated/SportsMissions_config.generated.h>

class SportsMissionsUILogic {
private:
	WeakPtr<SportsMissionsLogic> _logic;
	SportsMissionsConfig _config;
	IUIScripting* _UIScripting;
	VarsContext _UIContext;

	SportsMissionsUILogic() = default;

	void SetConfig(SportsMissionsConfig& config) { _config = config; };
	void SetUIScripting(IUIScripting* uiScripting) { _UIScripting = uiScripting; };
	void SetLogic(Ptr<SportsMissionsLogic>& logic) { _logic = MakeWeak(logic); };

	void Init()
	{
		_UIContext = Visual::Make<VarsContext>();
		_UIScripting->BindContext(_UIContext);

		// Referenced in window xml
		_UIContext->Set("WelcomeWindow.TitleLabel", GetLocalized(_config.local_context_config.variables.welcome_window.title_label_text_id));
		_UIContext->Set("WelcomeWindow.StartLabel", GetLocalized(_config.local_context_config.variables.welcome_window.start_button_text_id));
		// Called from lua behaviour
		_UIScripting->BindFunction("StartMission", [this](){ StartMission(); });
	}

	void StartMission()
	{
		if (_logic) { 
			_logic->StartMission();
		}
	}

	void Update()
	{
		// Referenced in window xml
		_UIContext.Set("WelcomeWindow.TimerValue", _logic->GetTimeRemaining());
	}

	// Logic...

public:
	Ptr<SportsMissionsUILogic> Instance(SportsMissionsConfig&& config, IUIScripting* uiScripting, Ptr<SportsMissionsLogic>& logic)
	{
		auto Instance = Core::Make<SportsMissionsUILogic>();
		Instance.SetConfig(config);
		Instance.SetUIScripting(uiScripting);
		Instance.SetLogic(logic);
		Instance->Init();
		return Instance;
	}
}