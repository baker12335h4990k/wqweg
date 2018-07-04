#include "Menu.h"
#include "Controls.h"
#include "Hooks.h" 
#include "Interfaces.h"
#include "CRC32.h"

#define WINDOW_WIDTH 635
#define WINDOW_HEIGHT 510

aristoispejawindow g_menu::window;

void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");
}

void SaveLegitCallbk()
{

	switch (g_menu::window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&g_menu::window, "1.cfg");
		break;
	case 1:
		GUI.SaveWindowState(&g_menu::window, "2.cfg");
		break;
	case 2:
		GUI.SaveWindowState(&g_menu::window, "3.cfg");
		break;
	case 3:
		GUI.SaveWindowState(&g_menu::window, "4.cfg");
		break;
	case 4:
		GUI.SaveWindowState(&g_menu::window, "5.cfg");
		break;
	case 5:
		GUI.SaveWindowState(&g_menu::window, "6.cfg");
		break;
	}
}

void LoadLegitCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");

	switch (g_menu::window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&g_menu::window, "1.cfg");

		break;
	case 1:
		GUI.LoadWindowState(&g_menu::window, "2.cfg");
		break;
	case 2:
		GUI.LoadWindowState(&g_menu::window, "3.cfg");
		break;
	case 3:
		GUI.LoadWindowState(&g_menu::window, "4.cfg");
		break;
	case 4:
		GUI.LoadWindowState(&g_menu::window, "5.cfg");
		break;
	case 5:
		GUI.LoadWindowState(&g_menu::window, "6.cfg");
		break;
	}
}


void UnLoadCallbk()
{
	DoUnload = true;
}

void aristoispejawindow::Setup()
{
	SetPosition(350, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("Wave Ware");

	RegisterTab(&RageBotTab);
	RegisterTab(&AntiAimtab);
	RegisterTab(&LegitbotTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&Movetab);
	RegisterTab(&ColorsTab);
    RegisterTab(&CSkinsTab);
	RegisterTab(&SettingsTab);
	RegisterTab(&MiscTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	RageBotTab.Setup();
	AntiAimtab.Setup();
	LegitbotTab.Setup();
	VisualsTab.Setup();
	Movetab.Setup();
	CSkinsTab.Setup();
	ColorsTab.Setup();
	SettingsTab.Setup();
	MiscTab.Setup();
	
#pragma endregion Setting up the settings buttons
}

void CRageBotTab::Setup()
{
	SetTitle("HvH");

	AimbotGroup.SetPosition(150, -50);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(220, 250);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);
	AimbotEnable.SetState(true);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("Auto fire", this, &AimbotAutoFire);
	AimbotAutoFire.SetState(true);

	AimbotFov2.SetFileId("aim_fov2");
	AimbotGroup.PlaceLabledControl("FOV Range", this, &AimbotFov2);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(180.f);
	AimbotGroup.PlaceLabledControl("", this, &AimbotFov);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup.PlaceLabledControl("Silent aim", this, &AimbotSilentAim);
	AimbotSilentAim.SetState(true);

	AutoRevolver.SetFileId("aim_autorevolver");
	AimbotGroup.PlaceLabledControl("Auto revolver", this, &AutoRevolver);
	AutoRevolver.SetState(true);

	Nadaaa.SetFileId("aim_gggggggg");
	AimbotGroup.PlaceLabledControl("Override", this, &Nadaaa);

	SomeShit.SetFileId("aim_naosei");
	SomeShit.SetKey(18);
	AimbotGroup.PlaceLabledControl("", this, &SomeShit);

	AimQuickStop.SetFileId("quick_stop");
	AimbotGroup.PlaceLabledControl("Quick Stop", this, &AimQuickStop);
	AimQuickStop.SetState(true);
		
	AccuracyAutoScope.SetFileId("auto_scoped");
	AimbotGroup.PlaceLabledControl("Auto scope", this, &AccuracyAutoScope);
	AccuracyAutoScope.SetState(true);

	AutoMinimumDamage.SetFileId("aim_autodamage");
	AimbotGroup.PlaceLabledControl("Auto damage", this, &AutoMinimumDamage);
	AutoMinimumDamage.SetState(true);

	AutoHitChance.SetFileId("aim_autohitchance");
	AimbotGroup.PlaceLabledControl("Auto Hit chance", this, &AutoHitChance);
	AutoHitChance.SetState(true);

	hitchance2.SetFileId("aim_autohitchance2");
	AimbotGroup.PlaceLabledControl("Hit chance", this, &hitchance2);

	AccuracyHitchance.SetFileId("hit_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(0);
	AimbotGroup.PlaceLabledControl("", this, &AccuracyHitchance);

	mindamage2.SetFileId("aim_autodamage2");
	AimbotGroup.PlaceLabledControl("Minimun damage", this, &mindamage2);

	AccuracyMinimumDamage.SetFileId("minimum_dmg");
	AccuracyMinimumDamage.SetBoundaries(0, 100);
	AccuracyMinimumDamage.SetValue(0);
	AimbotGroup.PlaceLabledControl("", this, &AccuracyMinimumDamage);

#pragma endregion Aimbot Controls Get Setup in here

	Hitbox.SetPosition(200, 210);
	Hitbox.SetText("hitscan head");
	Hitbox.SetSize(220, 250);
	RegisterControl(&Hitbox);

	Hitboxhead.SetFileId("aim_head");
	Hitbox.PlaceLabledControl("Head", this, &Hitboxhead);
	Hitboxhead.SetState(true);

	Hitbox2.SetPosition(265, 210);
	Hitbox2.SetText("hitscan neck");
	Hitbox2.SetSize(220, 250);
	RegisterControl(&Hitbox2);

	Hitboxneck.SetFileId("aim_neck");
	Hitbox2.PlaceLabledControl("Neck", this, &Hitboxneck);
	Hitboxneck.SetState(true);

	Hitbox3.SetPosition(328, 210);
	Hitbox3.SetText("hitscan arms");
	Hitbox3.SetSize(220, 250);
	RegisterControl(&Hitbox3);

	Hitboxarms.SetFileId("aim_chest");
	Hitbox3.PlaceLabledControl("Arms", this, &Hitboxarms);
	Hitboxarms.SetState(true);

	Hitbox4.SetPosition(386, 210);
	Hitbox4.SetText("hitscan chest");
	Hitbox4.SetSize(220, 250);
	RegisterControl(&Hitbox4);

	Hitboxchest.SetFileId("aim_chest");
	Hitbox4.PlaceLabledControl("Chest", this, &Hitboxchest);
	Hitboxchest.SetState(true);

	Hitbox5.SetPosition(447, 210);
	Hitbox5.SetText("hitscan legs");
	Hitbox5.SetSize(220, 250);
	RegisterControl(&Hitbox5);

	Hitboxlegs.SetFileId("aim_legs");
	Hitbox5.PlaceLabledControl("Legs", this, &Hitboxlegs);
	Hitboxlegs.SetState(true);

#pragma region AntiAim
	AntiAimGroup.SetPosition(375, -50);
	AntiAimGroup.SetText("Accuracy");
	AntiAimGroup.SetSize(220, 250);
	RegisterControl(&AntiAimGroup);

	AimbotResolver2.SetFileId("aim_resolver");
	AntiAimGroup.PlaceLabledControl("Resolver", this, &AimbotResolver2);

	AimbotResolver.SetFileId("acc_resolver");
	AimbotResolver.AddItem("None");
	AimbotResolver.AddItem("Matchmaking");
	AntiAimGroup.PlaceLabledControl("", this, &AimbotResolver);
	AimbotResolver.SetIndex(1);

	TargetSelection2.SetFileId("aim_target2");
	AntiAimGroup.PlaceLabledControl("Target selection", this, &TargetSelection2);

	TargetSelection.SetFileId("tgt_selection");
	TargetSelection.AddItem("FOV");
	TargetSelection.AddItem("Far away");
	TargetSelection.AddItem("Lethal");
	TargetSelection.AddItem("Threat");
	TargetSelection.AddItem("2 shot");
	AntiAimGroup.PlaceLabledControl("", this, &TargetSelection);
	TargetSelection.SetIndex(2);


	Resolverfakewalk.SetFileId("acc_fakewalkfix");
	AntiAimGroup.PlaceLabledControl("Anim fix", this, &Resolverfakewalk);
	Resolverfakewalk.SetState(true);

	AccuracyResolverbrute.SetFileId("acc_resolverpitch");
	AntiAimGroup.PlaceLabledControl("Pitch correct", this, &AccuracyResolverbrute);
	AccuracyResolverbrute.SetState(true);

	EnginePrediction.SetFileId("acc_engineprediciton");
	AntiAimGroup.PlaceLabledControl("Engine predict", this, &EnginePrediction);
	EnginePrediction.SetState(true);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AntiAimGroup.PlaceLabledControl("Compescale recoil", this, &AccuracyRecoil);
	AccuracyRecoil.SetState(true);

	AccuracyAutoWall.SetFileId("acc_awall");
	AntiAimGroup.PlaceLabledControl("Penetrate walls", this, &AccuracyAutoWall);
	AccuracyAutoWall.SetState(true);

	AccuracyBacktracking.SetFileId("acc_bcktrk");
	AntiAimGroup.PlaceLabledControl("BackTrack", this, &AccuracyBacktracking);
	AccuracyBacktracking.SetState(true);

	TargetMultipoint.SetFileId("acc_multipoint");
	AntiAimGroup.PlaceLabledControl("Multi-point", this, &TargetMultipoint);
	TargetMultipoint.SetState(true);

	TargetPointscale2.SetFileId("acc_pt2");
	AntiAimGroup.PlaceLabledControl("Point scale", this, &TargetPointscale2);

	TargetPointscale.SetFileId("pointscale");
	TargetPointscale.SetBoundaries(0, 10);
	TargetPointscale.SetValue(6.f);
	AntiAimGroup.PlaceLabledControl("", this, &TargetPointscale);

	BaimIfUnderXHealth2.SetFileId("acc_baim2");
	AntiAimGroup.PlaceLabledControl("B-AIM if hp", this, &BaimIfUnderXHealth2);

	BaimIfUnderXHealth.SetFileId("baimifhp");
	BaimIfUnderXHealth.SetBoundaries(0, 100);
	BaimIfUnderXHealth.SetValue(35);
	AntiAimGroup.PlaceLabledControl("", this, &BaimIfUnderXHealth);


#pragma endregion  AntiAim controls get setup in here
}

void CLegitBot::Setup()
{
	SetTitle("Simple Legit");

	AimbotGroup.SetPosition(150, -50);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(220, 250);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);


	AccuracyBacktracking.SetFileId("accuracybacktracking");
	AimbotGroup.PlaceLabledControl("Backtrack", this, &AccuracyBacktracking);
}


void CAntiAimtab::Setup()
{
	SetTitle("Anti Aim");

	Antiaim.SetPosition(150, -50);
	Antiaim.SetText("anti-aim");
	Antiaim.SetSize(220, 250);
	RegisterControl(&Antiaim);

	AntiAimEnable.SetFileId("aa_enable");
	Antiaim.PlaceLabledControl("Enable", this, &AntiAimEnable);
	AntiAimEnable.SetState(true);

	inair2.SetFileId("inair_aa");
	Antiaim.PlaceLabledControl("Edge", this, &inair2);
	inair2.SetState(true);

	InAir.SetFileId("inair");
	InAir.AddItem("Stand");
	InAir.AddItem("Half spin");
	InAir.AddItem("Backwards");
	Antiaim.PlaceLabledControl("", this, &InAir);

	pitch2.SetFileId("pitch_aa");
	Antiaim.PlaceLabledControl("Pitch", this, &pitch2);

	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("None");
	AntiAimPitch.AddItem("Emotion");
	AntiAimPitch.AddItem("Minimal");
	AntiAimPitch.AddItem("Dynamic");
	AntiAimPitch.AddItem("Jitter");
	Antiaim.PlaceLabledControl("", this, &AntiAimPitch);
	AntiAimPitch.SetIndex(1);

	realyaw2.SetFileId("realyaw_aa");
	Antiaim.PlaceLabledControl("Yaw", this, &realyaw2);

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("None");
	AntiAimYaw.AddItem("Backwards");
	AntiAimYaw.AddItem("Jitter");
	AntiAimYaw.AddItem("Lowerbody");
	AntiAimYaw.AddItem("Dynamic Swap");
	AntiAimYaw.AddItem("Fast Spin");
	AntiAimYaw.AddItem("Auto");
	AntiAimYaw.AddItem("Manual");
	Antiaim.PlaceLabledControl("", this, &AntiAimYaw);
	AntiAimYaw.SetIndex(2);

	SWSwitchEnable.SetFileId("manualaa");
	Antiaim.PlaceLabledControl("Switch", this, &SWSwitchEnable);
	SWSwitchEnable.SetState(true);

	SWSwitchKey.SetFileId("swswitchkey");
	SWSwitchKey.SetKey(70);
	Antiaim.PlaceLabledControl("", this, &SWSwitchKey);

	lbydelta.SetFileId("lby_aa");
	Antiaim.PlaceLabledControl("LBY", this, &lbydelta);

	BreakLBY.SetFileId("aa_break");
	BreakLBY.AddItem("None");
	/* BreakLBY.AddItem("Custom°"); */ // Не вижу смысла в этой функции, пока здесь ничего не работает/I do not see the point in this function, until nothing works here
	BreakLBY.AddItem("135°");
	/* BreakLBY.AddItem("Cooming Soon°"); */ // Не вижу смысла в этой функции, пока здесь ничего не работает/I do not see the point in this function, until nothing works here
	Antiaim.PlaceLabledControl("", this, &BreakLBY);
	BreakLBY.SetIndex(1);

	Antilby.SetFileId("antilby");
	Antilby.SetBoundaries(0, 180);
	Antilby.SetValue(95);
	Antiaim.PlaceLabledControl("", this, &Antilby);

	AntiAim2.SetPosition(375, -50);
	AntiAim2.SetText("fakeyaw");
	AntiAim2.SetSize(220, 250);
	RegisterControl(&AntiAim2);
	
	fakeyaw2.SetFileId("fakeyaw_aa");
	AntiAim2.PlaceLabledControl("Fake yaw", this, &fakeyaw2);

	FakeYaw.SetFileId("fakeaa");
	FakeYaw.AddItem("None");
	FakeYaw.AddItem("180 Jitter");
	FakeYaw.AddItem("180 LBY");
	FakeYaw.AddItem("LBY Jitter");
	FakeYaw.AddItem("Free");
	FakeYaw.AddItem("Spin");
	AntiAim2.PlaceLabledControl("", this, &FakeYaw);
	FakeYaw.SetIndex(1);

	fakelag25.SetFileId("aa_fakelag4");
	AntiAim2.PlaceLabledControl("Fake-Lag", this, &fakelag25);
	fakelag25.SetState(true);

	fakelag23.SetFileId("aa_fakelag2");
	fakelag23.AddItem("None");
	fakelag23.AddItem("Maximum");
	AntiAim2.PlaceLabledControl("", this, &fakelag23);
	fakelag23.SetIndex(1);

	fakelag24.SetFileId("aa_fakelag3");
	fakelag24.AddItem("Max");
	AntiAim2.PlaceLabledControl("", this, &fakelag24);

	fakelag2.SetFileId("fakelag2");
	AntiAim2.PlaceLabledControl("Limit", this, &fakelag2);

	fakelagvalue2.SetFileId("fakelag3");
	fakelagvalue2.SetBoundaries(0.f, 20.f);
	fakelagvalue2.SetValue(20.f);
	AntiAim2.PlaceLabledControl("", this, &fakelagvalue2);

	onlands.SetFileId("on-land");
	AntiAim2.PlaceLabledControl("On land", this, &onlands);
	onlands.SetState(true);

	separado2.SetFileId("separado");
	AntiAim2.PlaceLabledControl("", this, &separado2);
	
}                                                                  

void CVisualTab::Setup()
{
	SetTitle("Visuals");

	OptionsGroup.SetPosition(150, -50);
	OptionsGroup.SetText("options");
	OptionsGroup.SetSize(220, 250);
	RegisterControl(&OptionsGroup);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	OptionsGroup.PlaceLabledControl("Enemies Only", this, &FiltersEnemiesOnly);
	FiltersEnemiesOnly.SetState(true);

	boxx22.SetFileId("otp_seperatebox");
	OptionsGroup.PlaceLabledControl("Box", this, &boxx22);

	OptionsBox.SetFileId("otr_showbox");
	OptionsBox.AddItem("None");
	OptionsBox.AddItem("Normal");
	OptionsGroup.PlaceLabledControl("", this, &OptionsBox);

	chams33.SetFileId("otp_seperetachams");
	OptionsGroup.PlaceLabledControl("Chams", this, &chams33);

	OptionsChams.SetFileId("esp_chams");
	OptionsChams.AddItem("None");
	OptionsChams.AddItem("3D");
	OptionsChams.AddItem("2D");
	OptionsGroup.PlaceLabledControl("", this, &OptionsChams);
	OptionsChams.SetIndex(1);

	FakeAngleChams.SetFileId("fakeangles");
	OptionsGroup.PlaceLabledControl("Fake Angles", this, &FakeAngleChams);

	OptionsGlow.SetFileId("otp_glow");
	OptionsGroup.PlaceLabledControl("Glow", this, &OptionsGlow);
	OptionsGlow.SetState(true);

	GlowZ.SetFileId("t_color_no_vis_b");
	GlowZ.SetBoundaries(0.f, 255.f);
	GlowZ.SetValue(255.f);
	OptionsGroup.PlaceLabledControl("", this, &GlowZ);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("Name", this, &OptionsName);
	OptionsName.SetState(true);

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl("Weapon", this, &OptionsWeapon);
	OptionsWeapon.SetState(true);

	OptionHealthEnable.SetFileId("opt_health");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionHealthEnable);
	OptionHealthEnable.SetState(true);

	//OptionsArmor.SetFileId("opt_armor");
	//OptionsGroup.PlaceLabledControl("armor", this, &OptionsArmor);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	cl_righthandse.SetFileId("cl_righthand");
	OptionsGroup.PlaceLabledControl("", this, &cl_righthandse);
	
	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("Info", this, &OptionsInfo);

	FiltersC4.SetFileId("bomb");
	OptionsGroup.PlaceLabledControl("C4", this, &FiltersC4);

	FiltersWeapons.SetFileId("ftr_weaponss");
	OptionsGroup.PlaceLabledControl("Weapons", this, &FiltersWeapons);
	FiltersWeapons.SetState(true);

	OtherNoScope.SetFileId("eff_noscope");
	OptionsGroup.PlaceLabledControl("No scope", this, &OtherNoScope);
	OtherNoScope.SetState(true);

	OtherNoVisualRecoil.SetFileId("eff_visrecoil");
	OptionsGroup.PlaceLabledControl("No visual recoil", this, &OtherNoVisualRecoil);
	OtherNoVisualRecoil.SetState(true);

	OtherNoFlash.SetFileId("otr_noflash");
	OptionsGroup.PlaceLabledControl("No flash ", this, &OtherNoFlash);
	OtherNoFlash.SetState(true);

	OtherNoSmoke.SetFileId("eff_nosmoke");
	OptionsGroup.PlaceLabledControl("No smoke", this, &OtherNoSmoke);
	OtherNoSmoke.SetState(true);

	ESPOther.SetPosition(375, -50);
	ESPOther.SetText("Accuracy");
	ESPOther.SetSize(220, 250);
	RegisterControl(&ESPOther);

	ManualaaIndicator.SetFileId("opt_aaindicaor");
	ESPOther.PlaceLabledControl("AA Indicator", this, &ManualaaIndicator);
	ManualaaIndicator.SetState(true);

	LBYIdicador.SetFileId("opt_indicaor");
	ESPOther.PlaceLabledControl("LBY Indicator", this, &LBYIdicador);
	LBYIdicador.SetState(true);

	BulletTracers.SetFileId("opt_tracers");
	ESPOther.PlaceLabledControl("BUllet Tracers", this, &BulletTracers);
	BulletTracers.AddItem("None");
	BulletTracers.AddItem("Materialized");
	BulletTracers.AddItem("*Soon* Laser");
	ESPOther.PlaceLabledControl("", this, &BulletTracers);
	BulletTracers.SetIndex(1);

	DamageIndicator.SetFileId("damageindicator");
	ESPOther.PlaceLabledControl("Show damage", this, &DamageIndicator);
	DamageIndicator.SetState(true);

	SpreadCrosshair.SetFileId("spreadcrosshair");
	SpreadCrosshair.SetState(true);
	ESPOther.PlaceLabledControl("Spread crosshair", this, &SpreadCrosshair);


	spreadslider.SetFileId("otr_spreadslider");
	spreadslider.SetBoundaries(0.f, 255.f);
	spreadslider.SetValue(40.f);
	ESPOther.PlaceLabledControl("", this, &spreadslider);

	SpecList.SetFileId("otr_speclist");
	ESPOther.PlaceLabledControl("Show spectators", this, &SpecList);
	SpecList.SetState(true);

	handdd22.SetFileId("otr_seperatehand");
	ESPOther.PlaceLabledControl("Hands", this, &handdd22);

	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("None");
	OtherNoHands.AddItem("Clear");
	OtherNoHands.AddItem("Dark");
	OtherNoHands.AddItem("Cham");
	OtherNoHands.AddItem("Rainbow");
	ESPOther.PlaceLabledControl("", this, &OtherNoHands);
	OtherNoHands.SetIndex(4);

	OtherCrosshair.SetFileId("otr_rsrinfo");
	ESPOther.PlaceLabledControl("Wallbang damage", this, &OtherCrosshair);
	OtherCrosshair.SetState(true);

	f2.SetFileId("fieldofview");
	ESPOther.PlaceLabledControl("Field of view", this, &f2);


	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(20.f);
	ESPOther.PlaceLabledControl("", this, &OtherFOV);

	NightMode.SetFileId("nightmode");
	ESPOther.PlaceLabledControl("Night mode", this, &NightMode);
	NightMode.SetState(true);

	AsWaEnable.SetFileId("colorsenable");
	ESPOther.PlaceLabledControl("Enable Colors", this, &AsWaEnable);

	ESPOther.PlaceLabledControl("            Asus", this, &asusamount);
	asusamount.SetFileId("otr_asusprops");
	asusamount.SetBoundaries(1.f, 100.f);
	asusamount.SetValue(100.f);
	

	FiltersPlayers.SetState(true);
	FiltersC4.SetState(true);
#pragma endregion Setting up the Options controls
}


void CColorTab::Setup()
{
	SetTitle("Settings");
#pragma region Visual Colors


	Colors.SetPosition(150, -50);
	Colors.SetText("Colors");
	Colors.SetSize(220, 250);
	RegisterControl(&Colors);
	


	a17.SetFileId("boxchecker");
	Colors.PlaceLabledControl("- Chams Visible", this, &a17);

	a7.SetFileId("otr_cricle90button");
	Colors.PlaceLabledControl("Chams Red", this, &a7);


	TColorVisR.SetFileId("t_color_vis_r");
	TColorVisR.SetBoundaries(0.f, 255.f);
	TColorVisR.SetValue(255.f);
	Colors.PlaceLabledControl("", this, &TColorVisR);

	a8.SetFileId("otr_criclebu77tton");
	Colors.PlaceLabledControl("Chams Green", this, &a8);

	TColorVisG.SetFileId("t_color_vis_g");
	TColorVisG.SetBoundaries(0.f, 255.f);
	TColorVisG.SetValue(50.f);
	Colors.PlaceLabledControl("", this, &TColorVisG);

	a9.SetFileId("otr_criclebut55ton");
	Colors.PlaceLabledControl("Chams Blue", this, &a10);

	TColorVisB.SetFileId("t_color_vis_b");
	TColorVisB.SetBoundaries(0.f, 255.f);
	TColorVisB.SetValue(255.f);
	Colors.PlaceLabledControl("", this, &TColorVisB);




	a28.SetFileId("seperate5");
	Colors.PlaceLabledControl("", this, &a28);

	a17.SetFileId("boxchecker");
	Colors.PlaceLabledControl("- Chams not Visible", this, &a17);
	a28.SetFileId("seperate5");
	Colors.PlaceLabledControl("", this, &a28);

	a11.SetFileId("otr_cricle66button");
	Colors.PlaceLabledControl("Chams Red", this, &a11);

	TColorNoVisR.SetFileId("t_color_no_vis_r");
	TColorNoVisR.SetBoundaries(0.f, 255.f);
	TColorNoVisR.SetValue(0.f);
	Colors.PlaceLabledControl("", this, &TColorNoVisR);

	a12.SetFileId("otr_criclebutton");
	Colors.PlaceLabledControl("Chams Green", this, &a12);

	TColorNoVisG.SetFileId("t_color_no_vis_g");
	TColorNoVisG.SetBoundaries(0.f, 255.f);
	TColorNoVisG.SetValue(75.f);
	Colors.PlaceLabledControl("", this, &TColorNoVisG);

	a13.SetFileId("otr_criclebu77tton");
	Colors.PlaceLabledControl("Chams Blue", this, &a13);

	TColorNoVisB.SetFileId("t_color_no_vis_b");
	TColorNoVisB.SetBoundaries(0.f, 255.f);
	TColorNoVisB.SetValue(255.f);
	Colors.PlaceLabledControl("", this, &TColorNoVisB);





	a28.SetFileId("seperate5");
	Colors.PlaceLabledControl("", this, &a28);

	a17.SetFileId("boxchecker");
	Colors.PlaceLabledControl("-Glow color", this, &a17);
	a28.SetFileId("seperate5");
	Colors.PlaceLabledControl("", this, &a28);

	a11.SetFileId("otr_cricle66button");
	Colors.PlaceLabledControl("Glow Red", this, &a11);

	GlowR.SetFileId("t_color_no_vis_r");
	GlowR.SetBoundaries(0.f, 255.f);
	GlowR.SetValue(0.f);
	Colors.PlaceLabledControl("", this, &GlowR);

	a12.SetFileId("otr_criclebutton");
	Colors.PlaceLabledControl("Glow Green", this, &a12);

	GlowG.SetFileId("t_color_no_vis_g");
	GlowG.SetBoundaries(0.f, 255.f);
	GlowG.SetValue(75.f);
	Colors.PlaceLabledControl("", this, &GlowG);

	a13.SetFileId("otr_criclebu77tton");
	Colors.PlaceLabledControl("Glow Blue", this, &a13);

	GlowB.SetFileId("t_color_no_vis_b");
	GlowB.SetBoundaries(0.f, 255.f);
	GlowB.SetValue(255.f);
	Colors.PlaceLabledControl("", this, &GlowB);



	Colors2.SetPosition(375, -50);
	Colors2.SetText("others");
	Colors2.SetSize(220, 250);
	RegisterControl(&Colors2);

	a33.SetFileId("seperate1");
	Colors2.PlaceLabledControl("", this, &a33);

	a18.SetFileId("bullettracechecker");
	Colors2.PlaceLabledControl("- Bullet trace", this, &a18);

	a15.SetFileId("bullettracecheckerx");
	Colors2.PlaceLabledControl("", this, &a15);

	a29.SetFileId("otr_criclebutto5n");
	Colors2.PlaceLabledControl("CT Red", this, &a29);

	BULLETCT_R.SetFileId("bulletctR");
	BULLETCT_R.SetBoundaries(0.f, 255.f);
	BULLETCT_R.SetValue(0.f);
	Colors2.PlaceLabledControl("", this, &BULLETCT_R);

	a23.SetFileId("otr_criclebutto4n");
	Colors2.PlaceLabledControl("CT Green", this, &a23);

	BULLETCT_G.SetFileId("bulletctG");
	BULLETCT_G.SetBoundaries(0.f, 255.f);
	BULLETCT_G.SetValue(255.f);
	Colors2.PlaceLabledControl("", this, &BULLETCT_G);

	a24.SetFileId("otr_criclebutton4");
	Colors2.PlaceLabledControl("CT Blue", this, &a24);

	BULLETCT_B.SetFileId("bulletctB");
	BULLETCT_B.SetBoundaries(0.f, 255.f);
	BULLETCT_B.SetValue(255.f);
	Colors2.PlaceLabledControl("", this, &BULLETCT_B);


	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("", this, &a32);


	a25.SetFileId("otr_criclebutton3");
	Colors2.PlaceLabledControl("T Red", this, &a25);

	BULLET_T_R.SetFileId("bullettR");
	BULLET_T_R.SetBoundaries(0.f, 255.f);
	BULLET_T_R.SetValue(255.f);
	Colors2.PlaceLabledControl("", this, &BULLET_T_R);

	a26.SetFileId("otr_criclebutton2");
	Colors2.PlaceLabledControl("T Green", this, &a26);

	BULLET_T_G.SetFileId("bullettG");
	BULLET_T_G.SetBoundaries(0.f, 255.f);
	BULLET_T_G.SetValue(0.f);
	Colors2.PlaceLabledControl("", this, &BULLET_T_G);

	a27.SetFileId("otr_criclebutton1");
	Colors2.PlaceLabledControl("T Blue", this, &a27);

	BULLET_T_B.SetFileId("bullettB");
	BULLET_T_B.SetBoundaries(0.f, 255.f);
	BULLET_T_B.SetValue(255.f);
	Colors2.PlaceLabledControl("", this, &BULLET_T_B);

	


	//asus color
	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("", this, &a28);

	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("-Asus Color", this, &a28);

	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("", this, &a28);
	
	a28.SetFileId("otr_ared");
	Colors2.PlaceLabledControl("Asus Red", this, &a28);

	ACOLOR_r.SetFileId("bulletR");
	ACOLOR_r.SetBoundaries(0.f, 255.f);
	ACOLOR_r.SetValue(110.f);
	Colors2.PlaceLabledControl("", this, &ACOLOR_r);

	a29.SetFileId("otr_agreen");
	Colors2.PlaceLabledControl("Asus Green", this, &a29);

	ACOLOR_g.SetFileId("bulletG");
	ACOLOR_g.SetBoundaries(0.f, 255.f);
	ACOLOR_g.SetValue(0.f);
	Colors2.PlaceLabledControl("", this, &ACOLOR_g);

	a30.SetFileId("otr_ablue");
	Colors2.PlaceLabledControl("Asus Blue", this, &a30);

	ACOLOR_b.SetFileId("asusB");
	ACOLOR_b.SetBoundaries(0.f, 255.f);
	ACOLOR_b.SetValue(0.f);
	Colors2.PlaceLabledControl("", this, &ACOLOR_b);

	//Wall color
	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("", this, &a28);

	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("-Wall Color", this, &a28);

	a32.SetFileId("seperate2");
	Colors2.PlaceLabledControl("", this, &a28);

	a28.SetFileId("otr_ared");
	Colors2.PlaceLabledControl("Wall Red", this, &a28);

	WACOLOR_r.SetFileId("bulletR");
	WACOLOR_r.SetBoundaries(0.f, 255.f);
	WACOLOR_r.SetValue(0.f);
	Colors2.PlaceLabledControl("", this, &WACOLOR_r);

	a29.SetFileId("otr_agreen");
	Colors2.PlaceLabledControl("Wall Green", this, &a29);

	WACOLOR_g.SetFileId("bulletG");
	WACOLOR_g.SetBoundaries(0.f, 255.f);
	WACOLOR_g.SetValue(25.f);
	Colors2.PlaceLabledControl("", this, &WACOLOR_g);

	a30.SetFileId("otr_ablue");
	Colors2.PlaceLabledControl("Wall Blue", this, &a30);

	WACOLOR_b.SetFileId("asusB");
	WACOLOR_b.SetBoundaries(0.f, 255.f);
	WACOLOR_b.SetValue(85.f);
	Colors2.PlaceLabledControl("", this, &WACOLOR_b);


#pragma endregion
}

void Movement::Setup()
{
	SetTitle("Movement");

	Movetab.SetPosition(150, -50);
	Movetab.SetText("other");
	Movetab.SetSize(220, 250);
	RegisterControl(&Movetab);

	OtherAutoJump.SetFileId("otr_autojump");
	Movetab.PlaceLabledControl("AutoBhop", this, &OtherAutoJump);
	OtherAutoJump.SetState(true);

	OtherAutoStrafe.SetFileId("otr_strafe");
	Movetab.PlaceLabledControl("AutoStrafe", this, &OtherAutoStrafe);
	OtherAutoStrafe.SetState(true);

	OtherCircle.SetFileId("otr_criclebutton");
	Movetab.PlaceLabledControl("Circle Strafe", this, &OtherCircle);

}

 void SkinsTab::Setup() 
{
	SetTitle("Skins");
	Skinss.SetPosition(150, -50);
	Skinss.SetText("other");
	Skinss.SetSize(220, 250);
	RegisterControl(&Skinss);


	SkinsEnable.SetFileId("skins");
	Skinss.PlaceLabledControl("Enable Skins", this, &SkinsEnable);

	SkinApply.SetText("Apply");
	SkinApply.SetCallback(KnifeApplyCallbk);
	SkinApply.SetPosition(270, 290);
	SkinApply.SetSize(100, 40);
	Skinss.PlaceLabledControl("Apply", this, &SkinApply);
	RegisterControl(&SkinApply);

	a32.SetFileId("seperate2");
	Skinss.PlaceLabledControl("Knife Model", this, &a28);

	KnifeModel.SetFileId("aut_buyweapon");
	KnifeModel.AddItem("None");
	KnifeModel.AddItem("Bayonet");
	KnifeModel.AddItem("Bowie Knife" );
	KnifeModel.AddItem("Butterfly Knife");
	KnifeModel.AddItem("Flachion Knife");
	KnifeModel.AddItem("Flip Knife");
	KnifeModel.AddItem("Gut Knife");
	KnifeModel.AddItem("Huntsman Knife");
	KnifeModel.AddItem("Karambit");
	KnifeModel.AddItem("M9 Bayonet");
	KnifeModel.AddItem("Daggers");
	Skinss.PlaceLabledControl("", this, &KnifeModel);

	a32.SetFileId("seperate2");
	Skinss.PlaceLabledControl("", this, &a28);
	a32.SetFileId("seperate2");
	Skinss.PlaceLabledControl("Knife Skin", this, &a28);

	KnifeSkin.SetFileId("aut_buyweapon");
	KnifeSkin.AddItem("None");
	KnifeSkin.AddItem("Forest DDPAT");
	KnifeSkin.AddItem("Crimson Web");
	KnifeSkin.AddItem("Bone Mask");
	KnifeSkin.AddItem("Fade");
	KnifeSkin.AddItem("Night");
	KnifeSkin.AddItem("Blue Steel");
	KnifeSkin.AddItem("Stained");
	KnifeSkin.AddItem("Case Hardened");
	KnifeSkin.AddItem("Slaughter");
	KnifeSkin.AddItem("Safari Mesh");
	KnifeSkin.AddItem("Boreal Forest");
	KnifeSkin.AddItem("Ultra Violet");
	KnifeSkin.AddItem("Urban Masked");
	KnifeSkin.AddItem("Scorched");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Tiger Tooth");
	KnifeSkin.AddItem("Damascus Steel 1");
	KnifeSkin.AddItem("Damascus Steel 2");
	KnifeSkin.AddItem("Marble Fade");
	KnifeSkin.AddItem("Rust Coat");
	KnifeSkin.AddItem("Ruby");
	KnifeSkin.AddItem("Sapphire");
	KnifeSkin.AddItem("Doppler Blackpearl");
	KnifeSkin.AddItem("Doppler Phase 1");
	KnifeSkin.AddItem("Doppler Phase 2");
	KnifeSkin.AddItem("Doppler Phase 3");
	KnifeSkin.AddItem("Doppler Phase 4");
	KnifeSkin.AddItem("Gamma Phase 1");
	KnifeSkin.AddItem("Gamma Phase 2");
	KnifeSkin.AddItem("Gamma Phase 3");
	KnifeSkin.AddItem("Gamma Phase 4");
	KnifeSkin.AddItem("Emerald");
	KnifeSkin.AddItem("Lore");

	Skinss.PlaceLabledControl("", this, &KnifeSkin);
} 

void CSettingsTab::Setup()
{
    SetTitle("Misc");

    MiscGroup.SetPosition(150, -50);
    MiscGroup.SetText("other");
    MiscGroup.SetSize(220, 250);
    RegisterControl(&MiscGroup);

	autobuy.SetFileId("auto_buy");
	MiscGroup.PlaceLabledControl("Auto Buy Items", this, &autobuy);


	BuyBot.SetFileId("aut_buyweapon");
	BuyBot.AddItem("None");
	BuyBot.AddItem("SSG08");
	BuyBot.AddItem("SCAR20");
	BuyBot.AddItem("Negev");
	MiscGroup.PlaceLabledControl("", this, &BuyBot);
	BuyBot.SetIndex(2);

	BuyBotPistol.SetFileId("aut_buyweaponpistol");
	BuyBotPistol.AddItem("none");
	BuyBotPistol.AddItem("Berettas");
	BuyBotPistol.AddItem("Revolver");
	MiscGroup.PlaceLabledControl("", this, &BuyBotPistol);
	BuyBotPistol.SetIndex(1);

	BuyBotGrenades.SetFileId("aut_buyweaponzeus");
	BuyBotGrenades.AddItem("None");
	BuyBotGrenades.AddItem("Zeus + Kit Grenades");
	BuyBotGrenades.AddItem("Zeus + Defuser + Kit Grenades");
	MiscGroup.PlaceLabledControl("", this, &BuyBotGrenades);
	BuyBotGrenades.SetIndex(2);

	Logs2.SetFileId("auto_nofications");
	MiscGroup.PlaceLabledControl("", this, &Logs2);

	Logs.SetFileId("auto_noficaitins");
	Logs.AddItem("None");
	Logs.AddItem("On");
	MiscGroup.PlaceLabledControl("", this, &Logs);

	FakePingExploit.SetFileId("otr_fakepingexploit");
	MiscGroup.PlaceLabledControl("Fake latency nosafe*", this, &FakePingExploit);

	FakePingValue.SetFileId("auto_fakelatencyslider");
	FakePingValue.SetBoundaries(0.f, 800.f);
	FakePingValue.SetValue(0.f);
	MiscGroup.PlaceLabledControl("", this, &FakePingValue);

	//other tab 2 in supremacy

	misctabzin2.SetPosition(375, -50);
	misctabzin2.SetText("others");
	misctabzin2.SetSize(220, 250);
	RegisterControl(&misctabzin2);

	misctabzin2.PlaceLabledControl("HitMarker", this, &OtherHitmarker);
	OtherHitmarker.SetFileId("hitmarkersound");
	OtherHitmarker.AddItem("Off");
	OtherHitmarker.AddItem("COD");
	OtherHitmarker.AddItem("Metalic");
	OtherHitmarker.AddItem("Custom");
	OtherHitmarker.SetIndex(2);
	

	m4.SetFileId("auto_4");
	misctabzin2.PlaceLabledControl("Ragdoll force", this, &m4);
	m4.SetState(true);

	                         
	m6.SetFileId("auto_6");
	misctabzin2.PlaceLabledControl("Preserve Killfeed", this, &m6);
	m6.SetState(true);

}

void CMiscTab::Setup()
{
	SetTitle("Other");

#pragma region Other
	OtherGroup.SetPosition(150, -50);
	OtherGroup.SetText("other");
    OtherGroup.SetSize(220, 250);
	RegisterControl(&OtherGroup);
	
	clantag22.SetFileId("otr_seperateclantag");
	OtherGroup.PlaceLabledControl("Clantag", this, &clantag22);

	OtherClantag.SetFileId("otr_clantag");
	OtherClantag.AddItem("None");
	OtherClantag.AddItem("Static");
	OtherClantag.AddItem("Moving");
	OtherGroup.PlaceLabledControl("", this, &OtherClantag);

	AutoPistol.SetFileId("otr_autopistol");
	OtherGroup.PlaceLabledControl("Auto pistol", this, &AutoPistol);
	AutoPistol.SetState(true);

	OtherThirdperson.SetFileId("aa_thirdpsr");
	OtherGroup.PlaceLabledControl("Thirdperson", this, &OtherThirdperson);
	OtherThirdperson.SetState(true);

	OtherThirdpersonRange.SetFileId("thirdpersonrange");
	OtherThirdpersonRange.SetBoundaries(1, 1000);
	OtherThirdpersonRange.SetValue(180);
	OtherGroup.PlaceLabledControl("", this, &OtherThirdpersonRange);

	ThirdPersonKeyBind.SetFileId("aa_thirdpersonKey");
	ThirdPersonKeyBind.SetKey(86);
	OtherGroup.PlaceLabledControl("", this, &ThirdPersonKeyBind);

	OtherGroup2.SetPosition(375, -50);
	OtherGroup2.SetText("others");
	OtherGroup2.SetSize(220, 250);
	RegisterControl(&OtherGroup2);

	OtherSafeMode.SetState(true);

	configurations2.SetFileId("otr_seperatecfg");
	OtherGroup2.PlaceLabledControl("Configurations", this, &configurations2);

	lstPlayers.SetFileId("configs");
	lstPlayers.AddItem("1");
	lstPlayers.AddItem("2");
	lstPlayers.AddItem("3");
	lstPlayers.AddItem("4");
	lstPlayers.AddItem("5");
	lstPlayers.AddItem("6");
	OtherGroup2.PlaceLabledControl("", this, &lstPlayers);

	SaveButton3.SetFileId("save");
	SaveButton3.SetCallback(SaveLegitCallbk);
	OtherGroup2.PlaceLabledControl("", this, &SaveButton3);

	Seperate2.SetFileId("otr_separetegg");
	OtherGroup2.PlaceLabledControl("", this, &Seperate2);

	LoadButton3.SetFileId("load");
	LoadButton3.SetCallback(LoadLegitCallbk);
	OtherGroup2.PlaceLabledControl("", this, &LoadButton3);



#pragma endregion other random options


}

void g_menu::SetupMenu()
{
	window.Setup();

	GUI.RegisterWindow(&window);
	GUI.BindWindow(VK_INSERT, &window);
}

void g_menu::DoUIFrame()
{


	GUI.Update();
	GUI.Draw();
	
}

