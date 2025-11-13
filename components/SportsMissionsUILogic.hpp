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

		_UIContext->BindVariable("IsTutorialEnabled", _config.variables.is_tutorial_enabled);
		// More variables...
		_UIContext->BindFunction("OnWelcomeWindowClosed", [this](){ if (_logic) { _logic->OnWelcomeWindowClosed(); } });
		// More callbacks...
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