local LuaBehaviour = require('VsoLua.LuaBehaviour')

---@class BeatRushMainWindowBehaviour : LuaBehaviour
local BeatRushMainWindowBehaviour = {
	UIContext = Visual.NodeRef() -- can be moved to base class UILuaBehaviour
}

VisualUtils.DefineClass(BeatRushMainWindowBehaviour, LuaBehaviour)

function BeatRushMainWindowBehaviour:OnAttached()
	UIContext.BeatRush.OnWaitResultsStart.Subscribe(function(val)
		local Panel = self.GetNode("Panel")
		if (Panel) then
			Panel:Pause()
		else
			WriteError("Panel not found")
		end
	end, self._behaviour)

	UIContext.BeatRush.OnFinalResultsReward.Subscribe(function(val)
		-- We duplicate the property setter behaviour here because
		-- calling propertySetter:Apply directly is intrusive to the UI
		local RewardButtonHolder = self.GetNode("ButtonClaimRewardHolder")
		if (RewardButtonHolder) then
			RewardButtonHolder:active = true
		else
			WriteError("Node ButtonClaimRewardHolder not found")
		end
	end, self._behaviour)

	local RewardButtonHolder = self.GetNode("ButtonClaimRewardHolder")
	if (RewardButtonHolder) then
		local RewardButton = RewardButtonHolder.GetChild("Button")
		if (RewardButton) then
			RewardButton:GetSignal("click").Subscribe(function(val)
				UIContext.BeatRush.OnRewardClaim()
				RewardButtonHolder:active = false
			end, self._behaviour)
		else
			WriteError("Node ButtonClaimRewardHolder.Button not found")
		end
	else
		WriteError("Node ButtonClaimRewardHolder not found")
	end
end

function BeatRushMainWindowBehaviour:OnEnabled()
	local LogicUP = self.GetNode("LogicUP")
	-- this should be stripped in prod builds
	if (_DEBUG and LogicUP) then
		LogicUP:Load()
	end
end