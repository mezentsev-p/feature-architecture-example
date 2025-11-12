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
	Ptr<SportsMissionsPackDownloader> _packDownloader;
	Ptr<SportsMissionsScheduler> _scheduler;

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
		_DI.Add<SportsMissionsLogic>([&DI=_DI](){
			return SportsMissionsLogic::Instance(
					DI.Resolve<SportsMissionsConfig>(),
					DI.Resolve<SportsMissionsBalance>(),
					DI.Resolve<IMatch3>()
				);
		});

		// Compose
		_logic = _DI.Resolve<SportsMissionsLogic>();
		_packDownloader = _DI.Resolve(SportsMissionsPackDownloader);
		_scheduler = _DI.Resolve(SportsMissionsScheduler);

		return true;
	}
}