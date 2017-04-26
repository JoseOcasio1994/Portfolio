package Enemy
{	
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	public class Skater extends EnemyBase
	{				
		public function Skater(argParentClip:MovieClip)
		{
			super(argParentClip, "Assets/Art/imgSkater.swf");
			speed = 10;
			points = 3000;
			SetStats(mainStage.stageHeight - 115);
		}
		
		public override function MainLoop():void  
		{ 
			baseClip.x += speed; 			
		}
	}
}