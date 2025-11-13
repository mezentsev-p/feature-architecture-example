//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     SportsMissionsConfig data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include "json.hpp"

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::make_shared<T>(); else return std::make_shared<T>(j.get<T>());
        }
    };
    template <typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json & j, const std::optional<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::optional<T> from_json(const json & j) {
            if (j.is_null()) return std::make_optional<T>(); else return std::make_optional<T>(j.get<T>());
        }
    };
}
#endif

namespace quicktype {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_quicktype_HELPER
    #define NLOHMANN_UNTYPED_quicktype_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
    #endif

    #ifndef NLOHMANN_OPTIONAL_quicktype_HELPER
    #define NLOHMANN_OPTIONAL_quicktype_HELPER
    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, std::string property) {
        return get_heap_optional<T>(j, property.data());
    }
    template <typename T>
    inline std::optional<T> get_stack_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::optional<T>>();
        }
        return std::optional<T>();
    }

    template <typename T>
    inline std::optional<T> get_stack_optional(const json & j, std::string property) {
        return get_stack_optional<T>(j, property.data());
    }
    #endif

    struct ContextRegistratorConfig {
        std::string global_id;
        std::string context_component_holder;
    };

    struct EnableCondition {
        std::string lua;
    };

    struct CurrentStateValue {
        std::string type;
        std::string binding;
    };

    struct CurrentState {
        std::string type;
        CurrentStateValue value;
    };

    struct IsAllPacksDownloadedValue {
        std::string binding;
    };

    struct IsAllPacksDownloaded {
        IsAllPacksDownloadedValue value;
    };

    struct WelcomeWindow {
        std::string title_label_text_id;
        std::string start_button_text_id;
    };

    struct LocalContextConfigVariables {
        IsAllPacksDownloaded is_all_packs_downloaded;
        EnableCondition is_launch_conditions_satisfied;
        EnableCondition is_event_active;
        CurrentState current_state;
        EnableCondition is_min_player_level_reached;
        EnableCondition check_launch_requirements;
        WelcomeWindow welcome_window;
    };

    struct LocalContextConfig {
        std::string context_name;
        LocalContextConfigVariables variables;
    };

    struct ResourcePackDownloadConfig {
        std::string pack_id;
        EnableCondition enable_condition;
        EnableCondition required_condition;
    };

    struct Enabled {
        std::string condition_asset;
    };

    struct ScheduleConfigElement {
        std::string id;
        std::string type;
        std::optional<bool> cheat_launch;
        int64_t activate_start;
        int64_t activate_end;
        std::optional<Enabled> enabled;
    };

    struct ScheduleConfig {
        EnableCondition common_enabled_condition;
        std::vector<ScheduleConfigElement> schedule_configs;
        bool need_try_activate_on_activate;
        bool need_try_activate_on_update;
    };

    struct BalanceAsset {
        std::string asset_type;
        std::string asset_id;
    };

    struct SportsMissionConfig {
        BalanceAsset balance_asset;
        BalanceAsset rewards_balance_asset;
    };

    struct SportsMissionsConstsVariables {
        bool is_tutorial_enabled;
        bool show_tutorial_on_start;
        int64_t min_start_story_level;
    };

    struct SportsMissionsConsts {
        std::string context_name;
        SportsMissionsConstsVariables variables;
    };

    struct InProgress {
        std::vector<std::string> events_filter;
        std::vector<std::string> states_filter;
    };

    struct HandlersSettings {
        InProgress in_progress;
    };

    struct Transition {
        std::string target;
        std::vector<std::string> trigger_ids;
    };

    struct State {
        std::string name;
        std::vector<Transition> transitions;
    };

    struct StateMachineConfig {
        std::string default_state;
        std::vector<State> states;
        HandlersSettings handlers_settings;
    };

    struct SportsMissionsConfig {
        SportsMissionsConsts sports_missions_consts;
        LocalContextConfig local_context_config;
        ScheduleConfig schedule_config;
        SportsMissionConfig sports_mission_config;
        ResourcePackDownloadConfig resource_pack_download_config;
        ContextRegistratorConfig context_registrator_config;
        StateMachineConfig state_machine_config;
    };
}

namespace quicktype {
    void from_json(const json & j, ContextRegistratorConfig & x);
    void to_json(json & j, const ContextRegistratorConfig & x);

    void from_json(const json & j, EnableCondition & x);
    void to_json(json & j, const EnableCondition & x);

    void from_json(const json & j, CurrentStateValue & x);
    void to_json(json & j, const CurrentStateValue & x);

    void from_json(const json & j, CurrentState & x);
    void to_json(json & j, const CurrentState & x);

    void from_json(const json & j, IsAllPacksDownloadedValue & x);
    void to_json(json & j, const IsAllPacksDownloadedValue & x);

    void from_json(const json & j, IsAllPacksDownloaded & x);
    void to_json(json & j, const IsAllPacksDownloaded & x);

    void from_json(const json & j, WelcomeWindow & x);
    void to_json(json & j, const WelcomeWindow & x);

    void from_json(const json & j, LocalContextConfigVariables & x);
    void to_json(json & j, const LocalContextConfigVariables & x);

    void from_json(const json & j, LocalContextConfig & x);
    void to_json(json & j, const LocalContextConfig & x);

    void from_json(const json & j, ResourcePackDownloadConfig & x);
    void to_json(json & j, const ResourcePackDownloadConfig & x);

    void from_json(const json & j, Enabled & x);
    void to_json(json & j, const Enabled & x);

    void from_json(const json & j, ScheduleConfigElement & x);
    void to_json(json & j, const ScheduleConfigElement & x);

    void from_json(const json & j, ScheduleConfig & x);
    void to_json(json & j, const ScheduleConfig & x);

    void from_json(const json & j, BalanceAsset & x);
    void to_json(json & j, const BalanceAsset & x);

    void from_json(const json & j, SportsMissionConfig & x);
    void to_json(json & j, const SportsMissionConfig & x);

    void from_json(const json & j, SportsMissionsConstsVariables & x);
    void to_json(json & j, const SportsMissionsConstsVariables & x);

    void from_json(const json & j, SportsMissionsConsts & x);
    void to_json(json & j, const SportsMissionsConsts & x);

    void from_json(const json & j, InProgress & x);
    void to_json(json & j, const InProgress & x);

    void from_json(const json & j, HandlersSettings & x);
    void to_json(json & j, const HandlersSettings & x);

    void from_json(const json & j, Transition & x);
    void to_json(json & j, const Transition & x);

    void from_json(const json & j, State & x);
    void to_json(json & j, const State & x);

    void from_json(const json & j, StateMachineConfig & x);
    void to_json(json & j, const StateMachineConfig & x);

    void from_json(const json & j, SportsMissionsConfig & x);
    void to_json(json & j, const SportsMissionsConfig & x);

    inline void from_json(const json & j, ContextRegistratorConfig& x) {
        x.global_id = j.at("globalId").get<std::string>();
        x.context_component_holder = j.at("contextComponentHolder").get<std::string>();
    }

    inline void to_json(json & j, const ContextRegistratorConfig & x) {
        j = json::object();
        j["globalId"] = x.global_id;
        j["contextComponentHolder"] = x.context_component_holder;
    }

    inline void from_json(const json & j, EnableCondition& x) {
        x.lua = j.at("lua").get<std::string>();
    }

    inline void to_json(json & j, const EnableCondition & x) {
        j = json::object();
        j["lua"] = x.lua;
    }

    inline void from_json(const json & j, CurrentStateValue& x) {
        x.type = j.at("type").get<std::string>();
        x.binding = j.at("binding").get<std::string>();
    }

    inline void to_json(json & j, const CurrentStateValue & x) {
        j = json::object();
        j["type"] = x.type;
        j["binding"] = x.binding;
    }

    inline void from_json(const json & j, CurrentState& x) {
        x.type = j.at("type").get<std::string>();
        x.value = j.at("value").get<CurrentStateValue>();
    }

    inline void to_json(json & j, const CurrentState & x) {
        j = json::object();
        j["type"] = x.type;
        j["value"] = x.value;
    }

    inline void from_json(const json & j, IsAllPacksDownloadedValue& x) {
        x.binding = j.at("binding").get<std::string>();
    }

    inline void to_json(json & j, const IsAllPacksDownloadedValue & x) {
        j = json::object();
        j["binding"] = x.binding;
    }

    inline void from_json(const json & j, IsAllPacksDownloaded& x) {
        x.value = j.at("value").get<IsAllPacksDownloadedValue>();
    }

    inline void to_json(json & j, const IsAllPacksDownloaded & x) {
        j = json::object();
        j["value"] = x.value;
    }

    inline void from_json(const json & j, WelcomeWindow& x) {
        x.title_label_text_id = j.at("TitleLabelTextID").get<std::string>();
        x.start_button_text_id = j.at("StartButtonTextID").get<std::string>();
    }

    inline void to_json(json & j, const WelcomeWindow & x) {
        j = json::object();
        j["TitleLabelTextID"] = x.title_label_text_id;
        j["StartButtonTextID"] = x.start_button_text_id;
    }

    inline void from_json(const json & j, LocalContextConfigVariables& x) {
        x.is_all_packs_downloaded = j.at("IsAllPacksDownloaded").get<IsAllPacksDownloaded>();
        x.is_launch_conditions_satisfied = j.at("IsLaunchConditionsSatisfied").get<EnableCondition>();
        x.is_event_active = j.at("IsEventActive").get<EnableCondition>();
        x.current_state = j.at("CurrentState").get<CurrentState>();
        x.is_min_player_level_reached = j.at("IsMinPlayerLevelReached").get<EnableCondition>();
        x.check_launch_requirements = j.at("CheckLaunchRequirements").get<EnableCondition>();
        x.welcome_window = j.at("WelcomeWindow").get<WelcomeWindow>();
    }

    inline void to_json(json & j, const LocalContextConfigVariables & x) {
        j = json::object();
        j["IsAllPacksDownloaded"] = x.is_all_packs_downloaded;
        j["IsLaunchConditionsSatisfied"] = x.is_launch_conditions_satisfied;
        j["IsEventActive"] = x.is_event_active;
        j["CurrentState"] = x.current_state;
        j["IsMinPlayerLevelReached"] = x.is_min_player_level_reached;
        j["CheckLaunchRequirements"] = x.check_launch_requirements;
        j["WelcomeWindow"] = x.welcome_window;
    }

    inline void from_json(const json & j, LocalContextConfig& x) {
        x.context_name = j.at("contextName").get<std::string>();
        x.variables = j.at("variables").get<LocalContextConfigVariables>();
    }

    inline void to_json(json & j, const LocalContextConfig & x) {
        j = json::object();
        j["contextName"] = x.context_name;
        j["variables"] = x.variables;
    }

    inline void from_json(const json & j, ResourcePackDownloadConfig& x) {
        x.pack_id = j.at("packId").get<std::string>();
        x.enable_condition = j.at("enableCondition").get<EnableCondition>();
        x.required_condition = j.at("requiredCondition").get<EnableCondition>();
    }

    inline void to_json(json & j, const ResourcePackDownloadConfig & x) {
        j = json::object();
        j["packId"] = x.pack_id;
        j["enableCondition"] = x.enable_condition;
        j["requiredCondition"] = x.required_condition;
    }

    inline void from_json(const json & j, Enabled& x) {
        x.condition_asset = j.at("conditionAsset").get<std::string>();
    }

    inline void to_json(json & j, const Enabled & x) {
        j = json::object();
        j["conditionAsset"] = x.condition_asset;
    }

    inline void from_json(const json & j, ScheduleConfigElement& x) {
        x.id = j.at("id").get<std::string>();
        x.type = j.at("type").get<std::string>();
        x.cheat_launch = get_stack_optional<bool>(j, "cheatLaunch");
        x.activate_start = j.at("activateStart").get<int64_t>();
        x.activate_end = j.at("activateEnd").get<int64_t>();
        x.enabled = get_stack_optional<Enabled>(j, "enabled");
    }

    inline void to_json(json & j, const ScheduleConfigElement & x) {
        j = json::object();
        j["id"] = x.id;
        j["type"] = x.type;
        j["cheatLaunch"] = x.cheat_launch;
        j["activateStart"] = x.activate_start;
        j["activateEnd"] = x.activate_end;
        j["enabled"] = x.enabled;
    }

    inline void from_json(const json & j, ScheduleConfig& x) {
        x.common_enabled_condition = j.at("commonEnabledCondition").get<EnableCondition>();
        x.schedule_configs = j.at("scheduleConfigs").get<std::vector<ScheduleConfigElement>>();
        x.need_try_activate_on_activate = j.at("needTryActivateOnActivate").get<bool>();
        x.need_try_activate_on_update = j.at("needTryActivateOnUpdate").get<bool>();
    }

    inline void to_json(json & j, const ScheduleConfig & x) {
        j = json::object();
        j["commonEnabledCondition"] = x.common_enabled_condition;
        j["scheduleConfigs"] = x.schedule_configs;
        j["needTryActivateOnActivate"] = x.need_try_activate_on_activate;
        j["needTryActivateOnUpdate"] = x.need_try_activate_on_update;
    }

    inline void from_json(const json & j, BalanceAsset& x) {
        x.asset_type = j.at("assetType").get<std::string>();
        x.asset_id = j.at("assetId").get<std::string>();
    }

    inline void to_json(json & j, const BalanceAsset & x) {
        j = json::object();
        j["assetType"] = x.asset_type;
        j["assetId"] = x.asset_id;
    }

    inline void from_json(const json & j, SportsMissionConfig& x) {
        x.balance_asset = j.at("balanceAsset").get<BalanceAsset>();
        x.rewards_balance_asset = j.at("rewardsBalanceAsset").get<BalanceAsset>();
    }

    inline void to_json(json & j, const SportsMissionConfig & x) {
        j = json::object();
        j["balanceAsset"] = x.balance_asset;
        j["rewardsBalanceAsset"] = x.rewards_balance_asset;
    }

    inline void from_json(const json & j, SportsMissionsConstsVariables& x) {
        x.is_tutorial_enabled = j.at("IS_TUTORIAL_ENABLED").get<bool>();
        x.show_tutorial_on_start = j.at("SHOW_TUTORIAL_ON_START").get<bool>();
        x.min_start_story_level = j.at("MIN_START_STORY_LEVEL").get<int64_t>();
    }

    inline void to_json(json & j, const SportsMissionsConstsVariables & x) {
        j = json::object();
        j["IS_TUTORIAL_ENABLED"] = x.is_tutorial_enabled;
        j["SHOW_TUTORIAL_ON_START"] = x.show_tutorial_on_start;
        j["MIN_START_STORY_LEVEL"] = x.min_start_story_level;
    }

    inline void from_json(const json & j, SportsMissionsConsts& x) {
        x.context_name = j.at("contextName").get<std::string>();
        x.variables = j.at("variables").get<SportsMissionsConstsVariables>();
    }

    inline void to_json(json & j, const SportsMissionsConsts & x) {
        j = json::object();
        j["contextName"] = x.context_name;
        j["variables"] = x.variables;
    }

    inline void from_json(const json & j, InProgress& x) {
        x.events_filter = j.at("eventsFilter").get<std::vector<std::string>>();
        x.states_filter = j.at("statesFilter").get<std::vector<std::string>>();
    }

    inline void to_json(json & j, const InProgress & x) {
        j = json::object();
        j["eventsFilter"] = x.events_filter;
        j["statesFilter"] = x.states_filter;
    }

    inline void from_json(const json & j, HandlersSettings& x) {
        x.in_progress = j.at("InProgress").get<InProgress>();
    }

    inline void to_json(json & j, const HandlersSettings & x) {
        j = json::object();
        j["InProgress"] = x.in_progress;
    }

    inline void from_json(const json & j, Transition& x) {
        x.target = j.at("target").get<std::string>();
        x.trigger_ids = j.at("triggerIds").get<std::vector<std::string>>();
    }

    inline void to_json(json & j, const Transition & x) {
        j = json::object();
        j["target"] = x.target;
        j["triggerIds"] = x.trigger_ids;
    }

    inline void from_json(const json & j, State& x) {
        x.name = j.at("name").get<std::string>();
        x.transitions = j.at("transitions").get<std::vector<Transition>>();
    }

    inline void to_json(json & j, const State & x) {
        j = json::object();
        j["name"] = x.name;
        j["transitions"] = x.transitions;
    }

    inline void from_json(const json & j, StateMachineConfig& x) {
        x.default_state = j.at("defaultState").get<std::string>();
        x.states = j.at("states").get<std::vector<State>>();
        x.handlers_settings = j.at("handlersSettings").get<HandlersSettings>();
    }

    inline void to_json(json & j, const StateMachineConfig & x) {
        j = json::object();
        j["defaultState"] = x.default_state;
        j["states"] = x.states;
        j["handlersSettings"] = x.handlers_settings;
    }

    inline void from_json(const json & j, SportsMissionsConfig& x) {
        x.sports_missions_consts = j.at("SportsMissions_Consts").get<SportsMissionsConsts>();
        x.local_context_config = j.at("LocalContextConfig").get<LocalContextConfig>();
        x.schedule_config = j.at("ScheduleConfig").get<ScheduleConfig>();
        x.sports_mission_config = j.at("SportsMissionConfig").get<SportsMissionConfig>();
        x.resource_pack_download_config = j.at("ResourcePackDownloadConfig").get<ResourcePackDownloadConfig>();
        x.context_registrator_config = j.at("ContextRegistratorConfig").get<ContextRegistratorConfig>();
        x.state_machine_config = j.at("StateMachineConfig").get<StateMachineConfig>();
    }

    inline void to_json(json & j, const SportsMissionsConfig & x) {
        j = json::object();
        j["SportsMissions_Consts"] = x.sports_missions_consts;
        j["LocalContextConfig"] = x.local_context_config;
        j["ScheduleConfig"] = x.schedule_config;
        j["SportsMissionConfig"] = x.sports_mission_config;
        j["ResourcePackDownloadConfig"] = x.resource_pack_download_config;
        j["ContextRegistratorConfig"] = x.context_registrator_config;
        j["StateMachineConfig"] = x.state_machine_config;
    }
}
