package Player.Control
{	
	import Player.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.ui.Keyboard;
	import flash.events.TimerEvent;
	import flash.utils.Timer
	
	public class PlayerControlScheme
	{		
		protected var mainStage:Stage;
		protected var poopCallback:Function;
		protected var bird:Bird;		
		protected var isStunned:Boolean = false;
		protected var isPaused:Boolean = false;
		protected var minStageX:Number;
		protected var maxStageX:Number;
		protected var stageCenterX:Number;		
		
		
		public function PlayerControlScheme(argStage:Stage, argBird:Bird, argPoopCallback:Function)
		{
			mainStage = argStage;
			stageCenterX = mainStage.stageWidth / 2;
			minStageX = 20;
			maxStageX = mainStage.stageWidth - 20;
			bird = argBird;
			poopCallback = argPoopCallback;
			
			
			
			trace("stageCenterX: " + stageCenterX);
			trace("maxStageX: " + maxStageX);
		}
		
		public function MainLoop(){}
		
		public function CleanUp (){}
		
		public function StunStarted (){}
		
		public function StunFinished (){}
		
		public function Pause(isTrue:Boolean){isTrue = true; }
	}
}