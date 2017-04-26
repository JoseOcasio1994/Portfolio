package UI
{
	import Player.*;
	import UI.*;
	import Audio.*;
	import flash.display.MovieClip;
	import flash.events.TextEvent;
	import flash.media.Sound;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.ui.Keyboard;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFieldType;
	import flash.text.TextFormat;
	import flash.utils.Timer;
	import flash.display.Stage;
	import flash.net.SharedObject;
	
	public class UIManager
	{
		static var uiManager;
		
		var stage :Stage;
		var mainClass	:MainManager;
		
		var stageWidth:int;
		var stageHeight:int;
		var stageCenterX:int;
		var stageCenterY:int;
		
		// Screens
		var menu_BG						:Renderable;
		var menu_StartBtn				:Renderable;
		var menu_InstructionBtn			:Renderable;
		var menu_CtrlFreak				:Renderable;
		var menu_OutOfCtrl				:Renderable;
		var instruction_BG				:Renderable;
		var instruction_BackToMainBtn	:Renderable;
		var fight_BG_BG					:Renderable;
		var fight_BG_MG					:Renderable;
		var fight_BG_FG					:Renderable;
		var fight_OutOfPoopBanner		:Renderable;
		var fight_OutOfTimeBanner		:Renderable;
		var gameover_BG					:Renderable;
		var gameover_SubmitBtn			:Renderable;
		var leaderboard_BG				:Renderable;
		var leaderboard_BackToMainBtn 	:Renderable;
		
		//Instance Symbols
		var scoreLabel					:TextField;
		var scoreValue					:TextField;
		var timeLabel					:TextField;
		var timeValue					:TextField;
		var poopLabel					:TextField;
		var poopValue					:TextField;
		var nameInput					:TextField;
		
		// Text
		var poopText:TextField 	= new TextField();
		var timerText:TextField = new TextField();
		var scoreText:TextField = new TextField();
		
		//Leaderboard
		var savedData:SharedObject 	= SharedObject.getLocal("game");			
		var localScoreData:Object 	= savedData.data.scores;
		var name1:TextField 		= new TextField();				
		var name2:TextField 		= new TextField();				
		var name3:TextField 		= new TextField();				
		var name4:TextField 		= new TextField();				
		var name5:TextField 		= new TextField();				
		var point1:TextField 		= new TextField();			
		var point2:TextField 		= new TextField();			
		var point3:TextField 		= new TextField();			
		var point4:TextField 		= new TextField();					
		var point5:TextField 		= new TextField();
		
		var poofs:Array = new Array();
		var popUps:Array = new Array();
		var pickUpTexts:Array = new Array();
		
		static var fgStartX:Number;
		static var bgStartX:Number;
		
		public function UIManager (main: MainManager)
		{
			//Reference
			uiManager 		= this;
			mainClass 		= main;
			stage 			= main.stage;
			stageWidth 		= stage.stageWidth;
			stageHeight		= stage.stageHeight;
			stageCenterX 	= stageWidth / 2;
			stageCenterY 	= stageHeight / 2;
			
			menu_BG 					= new Renderable(MainManager.BG_ParallaxBG, "Assets/Backgrounds/bgMain.swf", false);
			menu_StartBtn 				= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnStart.swf", false);
			menu_InstructionBtn 		= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnHowTo.swf", false);
			menu_CtrlFreak				= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnOutOfCtrl.swf", false);
			menu_OutOfCtrl				= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnCtrlFreak.swf", false);
			
			instruction_BG 				= new Renderable(MainManager.BG_ParallaxBG, "Assets/Backgrounds/bgInstructions.swf", false);
			instruction_BackToMainBtn 	= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnBack.swf", false);
			
			fight_BG_BG 				= new Renderable(MainManager.BG_ParallaxBG, "Assets/Backgrounds/ParallaxBG.swf", false);
			fight_BG_MG 				= new Renderable(MainManager.BG_ParallaxMG, "Assets/Backgrounds/ParallaxMG.swf", false);
			fight_BG_FG 				= new Renderable(MainManager.NonUIFGLayer, 	"Assets/Backgrounds/ParallaxFG.swf", false);
			fight_OutOfPoopBanner		= new Renderable(MainManager.UIFGLayer, 	"Assets/Banner/OutOfPoop.swf", 			false);
			fight_OutOfTimeBanner		= new Renderable(MainManager.UIFGLayer, 	"Assets/Banner/OutOfTime.swf", 			false);
				
			gameover_BG 				= new Renderable(MainManager.BG_ParallaxBG, "Assets/Backgrounds/bgGameOver.swf", false);
			gameover_SubmitBtn 			= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnSubmit.swf", false);
						
			leaderboard_BG				= new Renderable(MainManager.BG_ParallaxBG, "Assets/Backgrounds/bgLeaderboard.swf", false);
			leaderboard_BackToMainBtn	= new Renderable(MainManager.UIFGLayer, 	"Assets/Buttons/btnReplay.swf", false);
			
			//Set positions
			menu_BG.setX(stageCenterX);
			menu_BG.setY(stageCenterY);
			menu_StartBtn.setX(stageCenterX - 10);
			menu_StartBtn.setY(197);
			menu_InstructionBtn.setX(stageCenterX - 10);
			menu_InstructionBtn.setY(295);
			menu_CtrlFreak.setX(stageCenterX - 10);
			menu_CtrlFreak.setY(370);
			menu_OutOfCtrl.setX(stageCenterX - 10);
			menu_OutOfCtrl.setY(370);	
			
			instruction_BG.setX(stageCenterX);
			instruction_BG.setY(stageCenterY);
			instruction_BackToMainBtn.setX(stageWidth - 75);
			instruction_BackToMainBtn.setY(60);
			
			fight_BG_BG.setX(stageCenterX);
			fight_BG_BG.setY(stageCenterY);
			fight_BG_MG.setX(stageCenterX);
			fight_BG_MG.setY(stageCenterY);
			fight_BG_FG.setX(stageCenterX);
			fight_BG_FG.setY(stageHeight - 40);
			fgStartX = stageCenterX;
			bgStartX = stageCenterX;
			fight_OutOfPoopBanner.setX(stageCenterX);
			fight_OutOfPoopBanner.setY(stageCenterY);
			fight_OutOfTimeBanner.setX(stageCenterX);
			fight_OutOfTimeBanner.setY(stageCenterY);
			
			gameover_BG.setX(stageCenterX);
			gameover_BG.setY(stageCenterY);
			gameover_SubmitBtn.setX(450);
			gameover_SubmitBtn.setY(350);
			
			leaderboard_BG.setX(stageCenterX);
			leaderboard_BG.setY(stageCenterY);
			leaderboard_BackToMainBtn.setX(stageCenterX);
			leaderboard_BackToMainBtn.setY(350);			
			
			//Button events
			menu_StartBtn.getClip().addEventListener(MouseEvent.MOUSE_UP, Menu_StartBtnHandler);
			menu_InstructionBtn.getClip().addEventListener(MouseEvent.MOUSE_UP, Menu_InstructionBtnHandler);
			menu_CtrlFreak.getClip().addEventListener(MouseEvent.MOUSE_UP, Menu_ControlSwapHandler);
			menu_OutOfCtrl.getClip().addEventListener(MouseEvent.MOUSE_UP, Menu_ControlSwapHandler);
			instruction_BackToMainBtn.getClip().addEventListener(MouseEvent.MOUSE_UP, Instruction_BackToMainBtnHandler);
			gameover_SubmitBtn.getClip().addEventListener(MouseEvent.MOUSE_UP, Gameover_ToLeaderboardBtnHandler);
			leaderboard_BackToMainBtn.getClip().addEventListener(MouseEvent.MOUSE_UP, Leaderboard_BackToMainBtnHandler);
			
			//Reference then hide symbols
			scoreLabel 	= mainClass.ScoreLabel;
			scoreValue 	= mainClass.ScoreValue;
			timeLabel 	= mainClass.TimeLabel;
			timeValue 	= mainClass.TimeValue;
			poopLabel 	= mainClass.PoopLabel;
			poopValue 	= mainClass.PoopValue;
			nameInput 	= mainClass.NameInputField;
			name1 		= mainClass.Name1;
			name2 		= mainClass.Name2;
			name3 		= mainClass.Name3;
			name4 		= mainClass.Name4;
			name5 		= mainClass.Name5;
			point1 		= mainClass.Point1;
			point2 		= mainClass.Point2;
			point3 		= mainClass.Point3;
			point4 		= mainClass.Point4;
			point5 		= mainClass.Point5;
			mainClass.removeChild(scoreLabel);
			mainClass.removeChild(scoreValue);
			mainClass.removeChild(timeLabel);
			mainClass.removeChild(timeValue);
			mainClass.removeChild(poopLabel);
			mainClass.removeChild(poopValue);
			mainClass.removeChild(name1);
			mainClass.removeChild(name2);
			mainClass.removeChild(name3);
			mainClass.removeChild(name4);
			mainClass.removeChild(name5);
			mainClass.removeChild(point1);
			mainClass.removeChild(point2);
			mainClass.removeChild(point3);
			mainClass.removeChild(point4);
			mainClass.removeChild(point5);
			
			//Leaderboard
			if (localScoreData == null) 
			{
				trace("New game save created");
				localScoreData = { 	name1: "-",
									name2: "-",
									name3: "-",
									name4: "-",
									name5: "-",
									
									score1: "-",
									score2: "-",
									score3: "-",
									score4: "-",
									score5: "-"};
				savedData.data.scores = localScoreData;
				savedData.flush();
			}
			//Reveal the first scren
			DrawMenuScreen(true);
			AudioManager.PlayOpenMusic(true);
		}
		
		public function MakePopUpPoints(argPoints:int, xPos:Number, yPos:Number)
		{
			var popUp:PopUpPoints = new PopUpPoints(MainManager.UIFGLayer, argPoints);
			popUp.setX(xPos);
			popUp.setY(yPos - 50);
			
			popUps.push(popUp);
		}
		
		public function MakePoof (xPos:Number, yPos:Number)
		{
			var poof:Poof = new Poof(MainManager.NPCLayer);
			poof.setX(xPos);
			poof.setY(yPos - 50);
		}
		
		public function PicksUpLaxative (posX:Number, posY:Number)
		{			
			var mc:LaxativeMC = new LaxativeMC();
			mc.x = posX;
			mc.y = posY + 50;
			pickUpTexts.push(mc);
		}
		
		public function PicksUpFood (posX:Number, posY:Number)
		{
			var mc:FoodMC = new FoodMC();
			mc.x = posX;
			mc.y = posY + 50;
			pickUpTexts.push(mc);
		}
		
		public function PicksUpStun (posX:Number, posY:Number)
		{
			var mc:StunnedMC = new StunnedMC();
			mc.x = posX;
			mc.y = posY + 50;
			pickUpTexts.push(mc);
		}
		
		public function FightScreenEndBanner (timeOutOrPoopOut:Boolean)
		{
			if (timeOutOrPoopOut)
			{
				fight_OutOfTimeBanner.AttachToParent(true);
			}
			else
			{
				fight_OutOfPoopBanner.AttachToParent(true);
			}
		}
		
		public function GameOver ()
		{
			fight_OutOfTimeBanner.AttachToParent(false);
			fight_OutOfPoopBanner.AttachToParent(false);
			DrawFightLevelScreen(false);
			DrawGameOverScreen(true);
		}
		
		public function MainLoop (score:int, poop:int, time:int)
		{
			scoreValue.text = score.toString();
			timeValue.text 	= time.toString();
			poopValue.text 	= poop.toString();
						
			//Pop ups
			for (var i:int = popUps.length - 1; i >= 0; i--)
			{
				if (popUps[i].FinishedUpdate())
				{
					popUps[i] = null;
					popUps.splice(i, 1);
				}
			}
			
			//Pick up texts
			for (var j:int = pickUpTexts.length - 1; j >= 0; j--)
			{
				if (pickUpTexts[j].FinishedUpdate())
				{
					pickUpTexts[j] = null;
					pickUpTexts.splice(j, 1);
				}
			}
		}
		
		public static function Parallax (ratio:Number, amount:Number)
		{
			uiManager.fight_BG_FG.setX(ratio * amount + fgStartX);
				uiManager.fight_BG_BG.setX(-ratio * amount + bgStartX);			

		}
		
		//{DRAW AND HIDE SCREEN
		function DrawMenuScreen(argTrue:Boolean):void
		{
			menu_BG.AttachToParent(argTrue);			
			menu_StartBtn.AttachToParent(argTrue);					
			menu_InstructionBtn.AttachToParent(argTrue);			
			
			if (argTrue)
			{				
				menu_CtrlFreak.AttachToParent(MainManager.IsCtrlFreakOn());
				menu_OutOfCtrl.AttachToParent(!MainManager.IsCtrlFreakOn());
			}
			else
			{
				menu_CtrlFreak.AttachToParent(false);
				menu_OutOfCtrl.AttachToParent(false);
			}
		}
		
		function DrawInstructionsScreen(argTrue:Boolean):void
		{
			instruction_BG.AttachToParent(argTrue);			
			instruction_BackToMainBtn.AttachToParent(argTrue);			
		}
		
		function DrawFightLevelScreen(argTrue:Boolean):void
		{
			fight_BG_BG.AttachToParent(argTrue);
			fight_BG_MG.AttachToParent(argTrue);
			fight_BG_FG.AttachToParent(argTrue);
			
			AttachDetachTextfield(scoreLabel, argTrue);
			AttachDetachTextfield(scoreValue, argTrue);
			AttachDetachTextfield(timeLabel, argTrue);
			AttachDetachTextfield(timeValue, argTrue);
			AttachDetachTextfield(poopLabel, argTrue);
			AttachDetachTextfield(poopValue, argTrue);
			
			if (!argTrue)
			{
				for (var i:int = popUps.length - 1; i >= 0; i--)
				{
					popUps[i].AttachToParent(false);
					popUps[i] = null;
					popUps.splice(i, 1);
				}
			
				for (var j:int = pickUpTexts.length - 1; j >= 0; j--)
				{
					pickUpTexts[j].AttachToParent(false);
					pickUpTexts[j] = null;
					pickUpTexts.splice(j, 1);
				}
			}
		}
		
		function DrawGameOverScreen(argTrue:Boolean):void
		{			
			gameover_BG.AttachToParent(argTrue);
			//nameInput.text = "(Enter name)";
			gameover_SubmitBtn.AttachToParent(argTrue);
			gameover_SubmitBtn.AttachToParent(argTrue);
			if (argTrue)
			{
				MainManager.UIFGLayer.addChild(nameInput);
			}
		}
		
		function DrawLeaderBoardScreen(argTrue:Boolean):void
		{			
			leaderboard_BG.AttachToParent(argTrue);
			leaderboard_BackToMainBtn.AttachToParent(argTrue);	
			if (argTrue)
			{
				MainManager.UIFGLayer.removeChild(nameInput);
			}
		}
		//}
		
		//{BUTTONS
		function Menu_StartBtnHandler(e:MouseEvent):void
		{
			DrawMenuScreen(false);
			DrawFightLevelScreen(true);
			stage.focus = stage;
			mainClass.FightScreen_Start();
			AudioManager.PlayOpenMusic(false);
		}
		
		function Menu_InstructionBtnHandler(e:MouseEvent):void
		{
			DrawMenuScreen(false);
			DrawInstructionsScreen(true)
			stage.focus = stage;
			AudioManager.MenuSelection();
		}
		
		function Menu_ControlSwapHandler (e:MouseEvent):void
		{
			mainClass.ToggleCtrlFreakOn();
			DrawMenuScreen(true);
			AudioManager.MenuSelection();
		}
		
		function Instruction_BackToMainBtnHandler(e:MouseEvent):void
		{
			DrawMenuScreen(true);
			DrawInstructionsScreen(false)
			stage.focus = stage;
			AudioManager.MenuBack();
		}
		
		function Gameover_ToLeaderboardBtnHandler(e:MouseEvent):void
		{			
			DrawGameOverScreen(false);
			DrawLeaderBoardScreen(true);
			stage.focus = stage;	
			SaveScore();
			UpdateScore(true);
			AudioManager.MenuSelection();
		}
		
		function Leaderboard_BackToMainBtnHandler(e:MouseEvent):void 
		{
			UpdateScore(false);
			DrawLeaderBoardScreen(false);
			DrawMenuScreen(true);
			stage.focus = stage;
			AudioManager.MenuBack();
			AudioManager.PlayOpenMusic(true);
		}
		//}
		
		//{SCORES
		function UpdateScore (visible:Boolean)
		{
			if (visible)
			{
				name1.text 		= localScoreData.name1;
				name2.text 		= localScoreData.name2;
				name3.text 		= localScoreData.name3;
				name4.text 		= localScoreData.name4;
				name5.text 		= localScoreData.name5;			
				point1.text 	= localScoreData.score1;
				point2.text 	= localScoreData.score2;
				point3.text 	= localScoreData.score3;
				point4.text 	= localScoreData.score4;
				point5.text 	= localScoreData.score5;
			
				MainManager.UIFGLayer.addChild(name1);
				MainManager.UIFGLayer.addChild(name2);
				MainManager.UIFGLayer.addChild(name3);
				MainManager.UIFGLayer.addChild(name4);
				MainManager.UIFGLayer.addChild(name5);
				MainManager.UIFGLayer.addChild(point1);
				MainManager.UIFGLayer.addChild(point2);
				MainManager.UIFGLayer.addChild(point3);
				MainManager.UIFGLayer.addChild(point4);
				MainManager.UIFGLayer.addChild(point5);
			}
			else
			{
				MainManager.UIFGLayer.removeChild(name1);
				MainManager.UIFGLayer.removeChild(name2);
				MainManager.UIFGLayer.removeChild(name3);
				MainManager.UIFGLayer.removeChild(name4);
				MainManager.UIFGLayer.removeChild(name5);
				MainManager.UIFGLayer.removeChild(point1);
				MainManager.UIFGLayer.removeChild(point2);
				MainManager.UIFGLayer.removeChild(point3);
				MainManager.UIFGLayer.removeChild(point4);
				MainManager.UIFGLayer.removeChild(point5);
			}
		}
		
		function SaveScore():void 
		{
			if (mainClass.GetScore() >= localScoreData.score1 || localScoreData.score1 == "-" || localScoreData.score1 == "")
			{
				trace("Score 1: ", mainClass.GetScore() + ", Name 1: ", nameInput.text);
				localScoreData = { name1:nameInput.text,
								name2:localScoreData.name1,
								name3:localScoreData.name2,
								name4:localScoreData.name3,
								name5:localScoreData.name4,
								
								score1:mainClass.GetScore(),
								score2:localScoreData.score1,
								score3:localScoreData.score2,
								score4:localScoreData.score3,
								score5:localScoreData.score4 }
				savedData.data.scores = localScoreData;
				savedData.flush();
			}
			else if (mainClass.GetScore() >= localScoreData.score2 || localScoreData.score2 == "-" || localScoreData.score2 == "")	
			{
				trace("Score 2: ", mainClass.GetScore());
				localScoreData = { name1:localScoreData.name1,
								name2:nameInput.text,
								name3:localScoreData.name2,
								name4:localScoreData.name3,
								name5:localScoreData.name4,
								
								score1:localScoreData.score1,
								score2:mainClass.GetScore(),
								score3:localScoreData.score2,
								score4:localScoreData.score3,
								score5:localScoreData.score4 }
				savedData.data.scores = localScoreData;
				savedData.flush()				
			}
			else if (mainClass.GetScore() >= localScoreData.score3 || localScoreData.score3 == "-" || localScoreData.score3 == "")
			{
				trace("Score 3: ", mainClass.GetScore());
				localScoreData = { name1:localScoreData.name1,
								name2:localScoreData.name2,
								name3:nameInput.text,
								name4:localScoreData.name3,
								name5:localScoreData.name4,
								
								score1:localScoreData.score1,
								score2:localScoreData.score2,
								score3:mainClass.GetScore(),
								score4:localScoreData.score3,
								score5:localScoreData.score4 }
				savedData.data.scores = localScoreData;
				savedData.flush();				
			}
			else if (mainClass.GetScore() >= localScoreData.score4 || localScoreData.score4 == "-" || localScoreData.score4 == "")
			{
				trace("Score 4: ", mainClass.GetScore());
				localScoreData = { name1:localScoreData.name1,
								name2:localScoreData.name2,
								name3:localScoreData.name3,
								name4:nameInput.text,
								name5:localScoreData.name4,
								
								score1:localScoreData.score1,
								score2:localScoreData.score2,
								score3:localScoreData.score3,
								score4:mainClass.GetScore(),
								score5:localScoreData.score4 }
				savedData.data.scores = localScoreData;
				savedData.flush(); }	
			else if (mainClass.GetScore() >= localScoreData.score5 || localScoreData.score5 == "-" || localScoreData.score5 == "")
			{
				trace("Score 5: ", mainClass.GetScore());
				localScoreData = { name1:localScoreData.name1,
								name2:localScoreData.name2,
								name3:localScoreData.name3,
								name4:localScoreData.name4,
								name5:nameInput.text,
								
								score1:localScoreData.score1,
								score2:localScoreData.score2,
								score3:localScoreData.score3,
								score4:localScoreData.score4,
								score5:mainClass.GetScore() }
				savedData.data.scores = localScoreData;
				savedData.flush();
			}
		}
		//}
				
		function AttachDetachTextfield(text:TextField, attach:Boolean)
		{
			if (attach)
			{
				MainManager.UIFGLayer.addChild(text);
			}
			else if (MainManager.UIFGLayer.contains(text))
			{
				MainManager.UIFGLayer.removeChild(text);
			}
		}
	}
}