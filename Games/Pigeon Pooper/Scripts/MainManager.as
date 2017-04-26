package
{
	import UI.*;
	import Audio.*;
	import Player.*;
	import Enemy.*;
	import Cloud.*;
	import flash.display.InteractiveObject;
	import flash.display.MovieClip;
	import flash.media.Sound;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.utils.Timer;
	import flash.display.Stage;
	
	public class MainManager extends MovieClip
	{
		//Add MovieClip as children to these clips, in order to control which appears on top.
		public static var NonUIRootLayer:MovieClip = new MovieClip();
		public static var BG_ParallaxBG:MovieClip = new MovieClip(); //BG
		public static var BG_ParallaxMG:MovieClip = new MovieClip(); //BG
		public static var CloudLayer:MovieClip = new MovieClip();
		public static var NonNPCLayer:MovieClip = new MovieClip();
		public static var NPCLayer:MovieClip = new MovieClip();
		public static var NonUIFGLayer:MovieClip = new MovieClip(); //FG
		public static var UIFGLayer:MovieClip = new MovieClip();
		public static var BlackMaskLayer:MovieClip = new MovieClip(); //Top most layer
		
		static const gameMaxDuration:int = 60; //Seconds.
		static const maxAmmo:int = 30;
		static const poopIntervals:int = 500;
		
		static var ctrlFreakOn:Boolean = true;
		static var poopAmmo:int;
		static var mainManager:MainManager;
		
		// Objects
		var bird:Bird;
		var uiManager:UIManager;
		var audioManager:AudioManager;
		var enemyManager:EnemyManager;
		var cloudManager:CloudManager;
		var screenshake:ScreenShake;
		
		// Attributes		
		var gameState:String;
		var score:int;
		var time:Number;
		var paused:Boolean = false;
		var fightOver:Boolean = false;
		
		// Timers
		var fightScreenSession:Timer = new Timer(1000);
		var quickPauseDuration:Timer = new Timer(40);
		var noPoopConfirmDelay:Timer = new Timer(3000);
		var fightScreenEndDelay:Timer = new Timer(2000);
		
		//Properties
		public static function IsCtrlFreakOn():Boolean { return ctrlFreakOn; }
		
		public static function GetPoopIntervals():int { return poopIntervals; }
		
		public function ToggleCtrlFreakOn():Boolean { return ctrlFreakOn = !ctrlFreakOn; }
		
		public function GetScore():int { return score; }
		
		public function MainManager()
		{
			mainManager = this;
			
			stage.addChild(NonUIRootLayer);
			NonUIRootLayer.addChild(BG_ParallaxBG);
			NonUIRootLayer.addChild(BG_ParallaxMG);
			NonUIRootLayer.addChild(CloudLayer);
			NonUIRootLayer.addChild(NonNPCLayer);
			NonUIRootLayer.addChild(NPCLayer);
			NonUIRootLayer.addChild(NonUIFGLayer);
			stage.addChild(UIFGLayer);
			stage.addChild(BlackMaskLayer);
			
			this.removeChild(BlackMask);
			BlackMaskLayer.addChild(BlackMask);
			
			enemyManager = new EnemyManager(this);
			uiManager = new UIManager(this);
			cloudManager = new CloudManager();
			screenshake = new ScreenShake();
			gameState = GameState.MenuScreen;
			
			stage.addEventListener(Event.ENTER_FRAME, MainLoop);
			//stage.addEventListener(KeyboardEvent.KEY_DOWN, DebugFunction);
			quickPauseDuration.addEventListener(TimerEvent.TIMER, TimedUnpause);
			fightScreenSession.addEventListener(TimerEvent.TIMER, DecrementTime);
			noPoopConfirmDelay.addEventListener(TimerEvent.TIMER, FightScreenConfirmNoPoop);
			fightScreenEndDelay.addEventListener(TimerEvent.TIMER, GameOverScreen_Draw);
		}
		
		public static function QuickPause()
		{
			mainManager.PauseGame(true);
			mainManager.quickPauseDuration.start();
		}
		
		public static function SpendPoop():Boolean
		{
			if (poopAmmo > 0)
			{
				poopAmmo--;
				return true;
			}
			else
			{
				return false;
			}
		}
		
		function MainLoop(e:Event):void
		{
			if (gameState == GameState.FightScreen && !paused && !fightOver)
			{
				if (time <= 0)
				{
					FightScreenFinish(true);
				}
				else
				{
					bird.MainLoop();
					enemyManager.MainLoop();
					cloudManager.MainLoop();
					CollisionCheck();
					
					if (time == 10)
					{
						AudioManager.PlayTimerTick();
					}
					
					if (poopAmmo <= 0)
					{
						noPoopConfirmDelay.start();
					}
				}
				
				uiManager.MainLoop(score, poopAmmo, time);
			}
			
			screenshake.MainLoop();
		}
		
		function PauseGame(isTrue:Boolean)
		{
			if (fightOver)
			{
				bird.Pause(true);
				enemyManager.Pause(true);
				paused = true;
			}
			else
			{
				bird.Pause(isTrue);
				enemyManager.Pause(isTrue);
				paused = isTrue;
			}
			
			if (!isTrue)
			{
				quickPauseDuration.reset();
				quickPauseDuration.stop();
			}
		}
		
		function TimedUnpause(event:TimerEvent)
		{
			PauseGame(false);
		}
		
		//{Fight screen
		public function FightScreen_Start()
		{
			//Object initialization
			cloudManager.Start();
			gameState = GameState.FightScreen;
			enemyManager.FightLevelStart();
			bird = new Bird(NonUIFGLayer, this);
			AudioManager.PlayAmbience();
			
			//Variable initialization
			poopAmmo = maxAmmo;
			score = 0;
			time = gameMaxDuration;
			fightOver = false;
			paused = false;
			
			//Timer
			quickPauseDuration.reset();
			noPoopConfirmDelay.reset();
			
			fightScreenSession.start();
		}
		
		function FightScreenConfirmNoPoop(event:TimerEvent)
		{
			//trace("FightScreenConfirmNoPoop");
			noPoopConfirmDelay.stop();
			noPoopConfirmDelay.reset();
			
			if (poopAmmo <= 0 && !fightOver)
			{
				FightScreenFinish(false);
			}
			else
			{
				AudioManager.StopTimerTick ();
			}
		}
		
		function FightScreenFinish(timeOutOrPoopOut:Boolean)
		{
			fightOver = true;
			PauseGame(true);
			uiManager.FightScreenEndBanner(timeOutOrPoopOut);
			bird.PreCleanUp();
			
			//Clean up
			noPoopConfirmDelay.stop();
			AudioManager.FightScreenCleanUp();
			fightScreenEndDelay.start();
		
		}//}
		
		function GameOverScreen_Draw(event:TimerEvent)
		{
			fightScreenEndDelay.stop();
			fightScreenSession.stop();
			noPoopConfirmDelay.stop();
			quickPauseDuration.stop();
			fightScreenEndDelay.reset();
			fightScreenSession.reset();
			noPoopConfirmDelay.reset();
			quickPauseDuration.reset();
			
			
			gameState = GameState.GameOverScreen;
			cloudManager.CleanUp();
			enemyManager.CleanUp();
			bird.CleanUp();
			uiManager.GameOver();
		}
		
		function DecrementTime(timerEvent:TimerEvent):void
		{
			time--;
		}
		
		function CollisionCheck():void
		{
			var enemyArray:Array = enemyManager.GetEnemies();
			var poopArray:Array = bird.GetPoops();
			var foodArray:Array = enemyManager.GetFoods();
			var laxArray:Array = enemyManager.GetLaxes();
			
			for (var p:int = poopArray.length - 1; p >= 0; p--)
			{
				// Poop and Player
				if (poopArray[p].getClip().hitTestObject(bird.getClip()) && poopArray[p].Reflected)
				{
					bird.Stunned();
					poopArray[p].CleanUp();
					poopArray[p] = null;
					poopArray.splice(p, 1);
					uiManager.PicksUpStun(bird.getX(), bird.getY());
					break;
				}
				
				// Poop and Enemy
				for (var e:int = enemyArray.length - 1; e >= 0; e--)
				{
					if (p < 0)
						break;
					
					if (poopArray[p].getClip().hitTestObject(enemyArray[e].getClip()))
					{
						switch (true)
						{
						case enemyArray[e] is Skater: 
							RemoveEnemy(e);
							RemovePoop(p);
							p--;
							break;
						case enemyArray[e] is BusinessMan: 
							RemoveEnemy(e);
							RemovePoop(p);
							p--;
							break;
						case enemyArray[e] is Elderly: 
							EnemyManager.addFood(enemyArray[e].getClip().x, enemyArray[e].getClip().y);
							RemoveEnemy(e);
							RemovePoop(p);
							p--;
							break;
						case enemyArray[e] is EvilMana: 
							EnemyManager.addLax(enemyArray[e].getClip().x, enemyArray[e].getClip().y);
							RemoveEnemy(e);
							RemovePoop(p);
							p--;
							break;
						case enemyArray[e] is Baby: 
							if (enemyArray[e].GetIsCovered())
							{
								Bird.ReflectPoop(p);
							}
							else
							{
								if (enemyArray[e].getParent() != null)
								{
									enemyArray[e].getParent().LostBaby();
								}
								RemovePoop(p);
								RemoveEnemy(e);
								p--;
							}
							break;
						case enemyArray[e] is Mother: 
							if (enemyArray[e].baby != null)
							{
								enemyArray[e].baby.setParent(null);
								enemyArray[e].setPoints(350);
							}
							RemoveEnemy(e);
							RemovePoop(p);
							p--;
							break;
						
						case enemyArray[e] is Lady: 
							Bird.ReflectPoop(p);
							break;
						default: 
							trace("Error: Unknown enemy type. MainManager.CollisionCheck(). " + enemyArray[e]);
							break;
						}
					}
				}
			}
			
			// Player and Food
			for (var f:int = foodArray.length - 1; f >= 0; f--)
			{
				if (bird.getClip().hitTestObject(foodArray[f].getClip()))
				{
					score += foodArray[f].getPoints();
					poopAmmo += 3;
					uiManager.PicksUpFood(bird.getX(), bird.getY());
					EnemyManager.RemoveFood(f);
				}
			}
			
			// Player and Laxatives
			for (var l:int = laxArray.length - 1; l >= 0; l--)
			{
				if (bird.getClip().hitTestObject(laxArray[l].getClip()))
				{
					score -= laxArray[l].getPoints();
					uiManager.PicksUpLaxative(bird.getX(), bird.getY());
					bird.LaxativeActivated();
					EnemyManager.RemoveLax(l);
				}
			}
		}
		
		function RemoveEnemy(index:int)
		{
			var points:int = enemyManager.GetEnemies()[index].getPoints();
			var xPos:int = enemyManager.GetEnemies()[index].getClip().x;
			var yPos:int = enemyManager.GetEnemies()[index].getClip().y;
			
			score += points;
			uiManager.MakePoof(xPos, yPos);
			uiManager.MakePopUpPoints(points, xPos, yPos);
			ScreenShake.DoShake(true);
			EnemyManager.RemoveEnemy(index);
			AudioManager.PlayPoof();
		}
		
		function RemovePoop(index:int)
		{			
			Bird.RemovePoop(index);
			ScreenShake.DoShake(false);
		}
		
		//function DebugFunction(event:KeyboardEvent)
		//{
		//	if (event.keyCode == Keyboard.P)
		//	{
		//		//ScreenShake.DoShake(true);
		//		PauseGame(true);
		//		paused = true;
		//	}
		//	else if (event.keyCode == Keyboard.O)
		//	{
		//		PauseGame(false);
		//		paused = false;
		//	}
		//	else if (event.keyCode == Keyboard.ESCAPE && gameState == GameState.FightScreen) //Quit fighting level.
		//	{
		//		FightScreenTimesUp();
		//	}
		//}
	}
}