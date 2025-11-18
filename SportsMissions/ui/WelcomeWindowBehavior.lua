local LuaBehaviour = require('VsoLua.LuaBehaviour')

---@class WelcomeWindowBehaviour : LuaBehaviour
local WelcomeWindowBehaviour = {
	startButton = Visual.NodeRef(),
	timerAnimation = Visual.NodeRef(),
	backgroundAnimation = Visual.NodeRef()
}

VisualUtils.DefineClass(WelcomeWindowBehaviour, LuaBehaviour)

function WelcomeWindowBehaviour:OnAttached()
	if self.startButton then
		self.startButton.pressedSignal:Subscribe(function(val)
			Context:StartMission()
		end, self._behaviour)
	else
		WriteError("Start button not found")
	end
end

function WelcomeWindowBehaviour:OnEnabled()
	if (self.timerAnimation) then
		self.timerAnimation:startAnimation()
	end

	if (self.backgroundAnimation) then
		self.backgroundAnimation:startAnimation()
	end
end

function WelcomeWindowBehaviour:OnDisabled()
	if (self.timerAnimation) then
		self.timerAnimation:stopAnimation()
	end

	if (self.backgroundAnimation) then
		self.backgroundAnimation:stopAnimation()
	end
end