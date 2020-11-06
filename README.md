# D2UberMod
Enables Uber Tristram in singleplayer Diablo II v1.13c and v1.14d

![Mephisto](https://user-images.githubusercontent.com/71973715/97115205-26007300-16fe-11eb-9755-0f8fa927b03b.jpg)
![Diablo](https://user-images.githubusercontent.com/71973715/97115204-200a9200-16fe-11eb-9b5e-21cc0c1ab250.png)
![Baal](https://user-images.githubusercontent.com/71973715/97115213-2e58ae00-16fe-11eb-8b45-cd860e849bdb.jpg)

## Install guide:
#### With PlugY:
- Place `D2UberMod.dll` in the PlugY install directory
- Set DllToLoad in `PlugY.ini` to:
```
    DllToLoad=D2UberMod.dll
```
- Disable plugy uber quest in `PlugY.ini`:  
```
    [UBER QUEST]
    ActiveUberQuest=0
```

Plugy can load 2 dlls, setting either `DllToLoad=D2UberMod.dll` or `DllToLoad2=D2UberMod.dll` is fine. <br/>
If you are using D2SE place `D2UberMod.dll` in the `D2SE\CORES\1.13c` directory. `PlugY.ini` is also found in `D2SE\CORES\1.13c` and should be modified as shown above.

		
#### Without PlugY:
- inject `D2UberMod.dll` with the injector of your choice.

<br/>

### Changelog
[v0.20a](https://github.com/Snapchip/D2UberMod/releases/tag/v0.20a)
- Added support for Diablo II version 1.14d
- Fixed possible crash if the dll was unloaded while the game is running.

[v0.10a](https://github.com/Snapchip/D2UberMod/releases/tag/v0.10a)
- Uber Baal now casts [Chilling Armor](http://classic.battle.net/diablo2exp/monsters/act5-uberbaal.shtml)
- Fixed a bug where Uber Mephisto would not spawn the correct monsters
- Minor changes to Uber spawn locations

[v0.02a](https://github.com/Snapchip/D2UberMod/releases/tag/v0.02a)
- Some Uber AI fixes
- Ubers spawn minions!
- Uber Baal and Uber Diablo approach more often when they are far away from the player
	
