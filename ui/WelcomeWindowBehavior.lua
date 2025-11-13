local LuaBehaviour = require('VsoLua.LuaBehaviour')

---@class WelcomeWindowBehaviour : LuaBehaviour
local WelcomeWindowBehaviour = {
	isTutorialEnabled = Context.IsTutorialEnabled,
	closeButton = Visual.NodeRef(),
	tutorialText = Visual.NodeRef()
}

VisualUtils.DefineClass(WelcomeWindowBehaviour, LuaBehaviour)

function WelcomeWindowBehaviour:OnAttached()
	if closeButton then
		closeButton.pressedSignal:Subscribe(function(val)
			Context:OnWelcomeWindowClosed()
		end, self._behaviour)
	else
		WriteError("Close button not found")
	end

	if tutorialText then
		tutorialText:setProperty("visible", isTutorialEnabled)
	else
		WriteError("Tutorial text not found")
	end
end