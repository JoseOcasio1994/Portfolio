package Audio
{
	import flash.media.Sound;
	import flash.net.URLRequest;
	import flash.media.SoundChannel;
	
	public class AudioManager
	{
		static var clockTick			:CustomSound;
		static var pigeonSpawn			:CustomSound;
		static var poof					:CustomSound;
		static var poopFart				:CustomSound;
		static var poopSplat			:CustomSound;
		static var wind					:CustomSound;
		static var fightScreenAmbience	:CustomSound;
		static var babyCry				:CustomSound;
		static var skateBoard			:CustomSound;
		static var menuSelection		:CustomSound;
		static var openMusic			:CustomSound;
		
		static var skaters:Array = new Array();
		
		public static function PlayOpenMusic (isTrue:Boolean)
		{
			if (isTrue)
			{
				openMusic = new CustomSound("Sounds/OpenMusic1.mp3", 1);
			}
			else if (openMusic != null)
			{
				openMusic.stop();
				openMusic = null;
			}			
		}
		
		public static function PlayAmbience ()
		{
			fightScreenAmbience = new CustomSound("Sounds/Park2.mp3", 1);
		}
		
		public static function PlayPigeonSpawn ()
		{
			pigeonSpawn = new CustomSound("Sounds/PigeonCoo3.mp3", 1);
		}
		
		public static function PlayTimerTick ()
		{
			StopTimerTick ();
			clockTick = new CustomSound("Sounds/TimeRunningOut2.mp3", 1);
		}
		
		public static function StopTimerTick ()
		{
			if (clockTick != null)
			{
				clockTick.stop();
				clockTick = null;
			}
		}
		
		public static function PlayPoop ()
		{
			poopFart = new CustomSound("Sounds/Poop5.mp3", 1);
		}
		
		public static function PlayPoof ()
		{
			poof = new CustomSound("Sounds/Poof2.mp3", 1);
		}
		
		public static function PlayPoopSplat ()
		{
			poopSplat = new CustomSound("Sounds/PoopSplat1.mp3", 1);
		}
		
		//public static function PlaySkateboard ()
		//{
		//	if (isTrue)
		//	{
		//		skateBoard = new CustomSound("Sounds/Skateboard2.mp3", 1);
		//		skaters.push(skateBoard);
		//	}
		//}
		//
		//public static function RemoveSkateboard (index:int)
		//{
		//	if (skaters[index] != null)
		//	{
		//		skaters[index].stop();
		//	}
		//}
		
		public static function FightScreenCleanUp ()
		{
			if (fightScreenAmbience != null)
			{
				fightScreenAmbience.stop();
			}
			
			AudioManager.StopTimerTick ();
			
			StopTimerTick();
			
			for (var i:int = skaters.length -1; i >= 0; i--)
			{
				if (skaters[i] != null)
				{
					skaters[i].stop();
					skaters[i] = null;
					skaters[i].splice;
				}				
			}
		}
		
		public static function MenuSelection ()
		{
			menuSelection = new CustomSound("Sounds/Menu_Pick.mp3", 1);
		}
		
		public static function MenuBack ()
		{
			menuSelection = new CustomSound("Sounds/Menu_Back.mp3", 1);
		}
	}
}