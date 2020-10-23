# D2UberMod
Enables Uber Tristram in singleplayer Diablo II v1.13c


## Install guide:
#### With PlugY:
- Place the dll in the PlugY install directory
- Set DllToLoad in `PlugY.ini` to:
```
    DllToLoad=D2UberMod.dll
```
- Disable plugy uber quest in `PlugY.ini`:  
```
    [UBER QUEST]
    ActiveUberQuest=0
```
		
#### With PlugY and D2SE:
- Place the dll in the `D2SE\CORES\1.13c` directory
- Set DllToLoad in `PlugY.ini` found in `D2SE\CORES\1.13c` to:
 ```
    DllToLoad=D2UberMod.dll
```
- Disable plugy uber quest in `PlugY.ini`:  
```
    [UBER QUEST]
    ActiveUberQuest=0
```
		
#### Without PlugY:
- inject the dll with the injector of your choice.

<br/>

### Changelog
v0.10a
- Fixed an issue where Uber Mephisto would not spawn the correct monsters
- Minor changes to Uber spawn locations
	
v0.02a
- Some Uber AI fixes
- Ubers spawn minions!
- Uber Baal and Uber Diablo approach more often when they are far away from the player
	
