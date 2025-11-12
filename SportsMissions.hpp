#include <BasicDI.h>
#include <ServiceLocator>
#include <Common/IMatch3.h>
#include <Common/IPlayerInfo.h>

#include <generated/SportsMissions_config.generated.h>

class SportsMissionsLogic;
class SportsMissionsLoader;
class SportsMissionsScheduler;
class SportsMissionsUILogic;

class SportsMissions
{
private:
	DI::Container _DI;

	Ptr<SportsMissionsLogic> _logic;
	Ptr<SportsMissionsLoader> _loader;

public:
	bool Compose(ServiceLocator& sl) {
		// Common services
		_DI.Add<IMatch3>([](){ return sl.Locate<IMatch3>(); });
		_DI.Add<IPlayerInfo>([](){ return sl.Locate<IPlayerInfo>(); });

		// Configs
		_DI.Add<SportsMissionsConfig>([](){ 
			SportsMissionsConfig config;
			quicktype::from_json(Util::LoadJson("SportsMissions_config.json"), &config);
			return config; 
		});
		_DI.Add<ScheduleConfig>([&DI=_DI](){
			return DI.Resolve<SportsMissionsConfig>().schedule_config;
		});
		_DI.Add<ResourcePackDownloadConfig>([&DI=_DI](){
			return DI.Resolve<SportsMissionsConfig>().resource_pack_download_config;
		});
		_DI.Add<LocalContextConfigVariables>([&DI=_DI](){
			return DI.Resolve<SportsMissionsConfig>().local_context_config.variables;
		});

		// Balance
		_DI.Add<SportsMissionsBalance>([](){
			auto Balance = Core::MakeIntrusive<SportsMissionsBalance>();
			Balance->Init();
			return Balance;
		})

		// Components
		_DI.Add<SportsMissionsPackDownloader>([&DI=_DI](){
			return SportsMissionsPackDownloader::Instance(
					DI.Resolve<ResourcePackDownloadConfig>(),
					DI.Resolve<IPlayerInfo>()
				);
		});
		_DI.Add<SportsMissionsScheduler>([&DI=_DI](){
			return SportsMissionsScheduler::Instance(DI.Resolve<ScheduleConfig>())
		});
		_DI.Add<SportsMissionsLoader>([this, &DI=_DI](){
			return SportsMissionsLoader::Instance(
					DI.Resolve<LocalContextConfigVariables>(),
					DI.Resolve<SportsMissionsScheduler>(),
					DI.Resolve<SportsMissionsPackDownloader>(),
					this
				)
		});
		_DI.Add<SportsMissionsLogic>([&DI=_DI](){
			return SportsMissionsLogic::Instance(
					DI.Resolve<SportsMissionsConfig>(),
					DI.Resolve<SportsMissionsBalance>(),
					DI.Resolve<IMatch3>(),
					DI.Resolve<IPlayerInfo>()
				);
		});

		// Compose
		_loader = _DI.Resolve(SportsMissionsLoader);

		return true;
	}

	void OnLoaded()
	{
		_logic = _DI.Resolve<SportsMissionsLogic>();
	}
}