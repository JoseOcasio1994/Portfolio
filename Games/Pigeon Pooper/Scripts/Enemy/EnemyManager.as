package Enemy
{
	import Audio.*;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class EnemyManager
	{
		private static var enemies:Array = new Array();
		private static var foods:Array = new Array();
		private static var laxes:Array = new Array();
		
		private static var curEnemies:int = 0;
		private static var curUmbrellas:int = 0;
		
		private var maxEnemies:Number = 6;
		
		private var food:Food;
		private var lax:Lax;
		
		private var mainClass:MainManager;
		private var stage:Stage;
		
		//Timer
		private var spawnTimer:Timer = new Timer(1000);
		
		//Getters
		public function GetEnemies ():Array {return enemies; }
		
		public function GetFoods ():Array {return foods; }
		
		public function GetLaxes ():Array {return laxes;}	
		
		public function EnemyManager(main:MainManager)
		{
			mainClass = main;
			stage = main.stage;
		}
		
		public static function addFood(x:Number, y:Number):void
		{
			var food:Food = new Food(MainManager.NonNPCLayer);
			food.setX(x);
			food.setY(y);
			foods.push(food);
		}
		
		public static function addLax(x:Number, y:Number):void
		{
			var lax:Lax = new Lax(MainManager.NonNPCLayer);
			lax.setX(x);
			lax.setY(y);
			laxes.push(lax);
		}
		
		public static function RemoveEnemy(i:int)
		{
			enemies[i].removeSelf();
			enemies[i] = null;
			enemies.splice(i, 1);
			curEnemies--;
		}
		
		public static function RemoveLax (index:int)
		{
			laxes[index].removeSelf();
			laxes[index] = null;
			laxes.splice(index, 1);
		}
		
		public static function RemoveFood (index:int)
		{
			foods[index].removeSelf();
			foods[index] = null;
			foods.splice(index, 1);
		}
		
		public function FightLevelStart ()
		{	
			//InstantiateEnemy(4);
			spawnTimer.addEventListener(TimerEvent.TIMER, SpawnEnemy);
			spawnTimer.start();
		}
		
		public function MainLoop()
		{
			for (var i:int = enemies.length - 1; i >= 0; i--)
			{
				var enemy:EnemyBase = enemies[i];
				enemy.MainLoop();
				//SKATER: Check if skates outside of screen edge.
				if (enemy is Skater)
				{					
					if ((enemy.getClip().x > stage.stageWidth + enemy.getClip().width && enemy.facingRight) ||
						(enemy.getClip().x < -enemy.getClip().width && !enemy.facingRight))
					{
						enemy.removeSelf();
						enemies[i] = null;
						enemies.splice(i, 1);
						curEnemies--;
						//AudioManager.PlaySkateboard(false);
					}
				}
			}
			
			//FOOD
			for (var j:int = foods.length - 1; j >= 0; j--)
			{
				foods[j].MainLoop();
				if (foods[j].getClip().y > 300)
				{
					foods[j].removeSelf();
					foods[j] = null;
					foods.splice(j, 1);
				}
			}
			
			//LAXATIVES
			for (var k:int = laxes.length - 1; k >= 0; k--)
			{
				laxes[k].MainLoop();
				if (laxes[k].getClip().y > 300)
				{
					laxes[k].removeSelf();
					laxes[k] = null;
					laxes.splice(k, 1);
				}
			}					
		}
		
		public function CleanUp()
		{
			spawnTimer.stop();
			spawnTimer.reset();
			spawnTimer.removeEventListener(TimerEvent.TIMER, SpawnEnemy);
			
			for (var i:int = enemies.length - 1; i >= 0; i--)
			{
				RemoveEnemy(i);	
			}
			
			for (var k:int = 0; k < foods.length; k++)
			{
				foods[k].removeSelf();
				foods[k] = null;
			}
			
			for (var l:int = 0; k < laxes.length; l++)
			{
				laxes[l].removeSelf();
				laxes[l] = null;
			}
			
			enemies = new Array();
			foods = new Array();
		}
		
		public function Pause (isTrue:Boolean)
		{
			for each(var e in enemies)
			{
				e.Pause(isTrue);
			}
		}
		
		function SpawnEnemy(timerEvent:TimerEvent):void
		{			
			if (curEnemies < maxEnemies)
			{
				//Have 1 umbrella on screen - no more/less.
				if (curEnemies > 0 && curUmbrellas == 0)
				{
					InstantiateEnemy(6);//Umbrella
				}
				else
				{
					var dice:Number = Math.floor(Math.random() * 100 + 1);
					if (dice > 0 && dice <= 20)
						InstantiateEnemy(1);//Business
					else if (dice > 21  && dice <= 34)
						InstantiateEnemy(2);//Skate
					else if (dice > 35 && dice <= 54)
						InstantiateEnemy(3);//Elderly
					else if (dice > 55 && dice <= 74)
						InstantiateEnemy(4);//Mother
					else if (dice > 75 && dice <= 94)
						InstantiateEnemy(5);//EvilGrandma
					else if (dice > 95 && dice <=100)
						InstantiateEnemy(6); //Umbrella
				}
			}
		}
		
		function InstantiateEnemy(newEnemy:Number):void
		{
			var enemy:EnemyBase;
			switch (newEnemy)
			{			
				case 1: 
				{
					enemy = new BusinessMan(MainManager.NPCLayer);
					break;
				}				
				case 2: 
				{
					enemy = new Skater(MainManager.NPCLayer);
					//AudioManager.PlaySkateboard(true);
					break;
				}				
				case 3: 
				{
					enemy = new Elderly(MainManager.NPCLayer);
					break;
				}
				case 4: 
				{
					enemy = new Mother(MainManager.NPCLayer);
					
					var baby:EnemyBase = new Baby(MainManager.NPCLayer, Mother(enemy));
					Mother(enemy).AddBaby(Baby(baby));
					curEnemies++;
					baby.AttachToParent(true);
					enemies.push(baby);
					break;
				}		
				case 5: 
				{
					enemy = new EvilMana(MainManager.NPCLayer);
					break;
				}
				default: 
				{
					enemy = new Lady(MainManager.NPCLayer);
					curUmbrellas++;
					break;
				}			
			}
			enemy.AttachToParent(true);
			enemies.push(enemy);
			curEnemies++;
		}
	}
}