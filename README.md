<div align="center">
  <img src="logoDiscord.png" height="200" />
</div>

# Discord Bot Manager

## What is this?
The Discord Bot Manager is a terminal-based program that simplifies the process of creating Discord bots for users who may not be familiar with programming.

## What does it do?
It provides an easy way for individuals to create simple Discord bots without extensive programming knowledge.
> **Note:** Because this is a Terminal app without Servers its either you host the bot on your computer with the host feature in the app or use a hosting providor like heroku

## Is it free? 
Yes, the Discord Bot Manager is 100% free!

> **Note:** Currently, there is only a Windows 10 and 11 build available, and a Linux or macOS version is unlikely to be released.

---

## How to Install
1. **Download the latest Microsoft Visual C++ Redistributable**
   - get [Microsoft Visual C++ Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022) here.
   
3. **Download the latest release:**
   - Go to the [releases page](https://github.com/your-repo/releases) and download the latest ZIP file.

4. **Choose your installation location:**
   - You can install it anywhere, but it's recommended to use the `C:` drive for convenience.

5. **Extract the ZIP file:**
   - Extract the entire contents of the ZIP file to your chosen location.


### Set Up Environment Variable
Now that you have installed the Discord Bot Manager, create an environment variable for easy access from the terminal:

1. **Open System Properties:**
   - Search for "Environment Variables" in the search bar (located in the bottom left or right of your computer).

2. **Open Environment Variables:**
   - Click on "Edit the system environment variables."

3. **Access System Variables:**
   - In the System Properties window, click on the "Environment Variables" button at the bottom.

4. **Modify the Path Variable:**
   - In the "System variables" section, locate the `Path` variable and double-click it.

5. **Add New Path:**
   - In the "Edit Environment Variable" window, click "New" and paste the path to the folder where you extracted the Discord Bot Manager.

6. **Confirm Changes:**
   - Click "OK" to close all dialog boxes.

### Running the Application
To run the application, open the command prompt:

- Search for `cmd` in the search bar.
- Type `discordbot.exe` and hit Enter.

And just like that, you have successfully installed the Discord Bot Manager!

---

## How to Use It
The program is self-explanatory. Simply open the command prompt (CMD) and type `discordbot.exe` to launch the application.

---
## How to Update
If you Are updating from Version 1.0 delete login file in 
AppData\Roaming\discordBotManagerData
redownload from the steps above (you dont have to re do the env var again just reinstall in the same place)
relogin and youre commands will be saved

---
## FAQ

### How do I create a bot with its token?
Follow the [official Discord.js guide](https://discordjs.guide/preparations/setting-up-a-bot-application.html#creating-your-bot) to create your bot application.

### How do I get a Guild ID or Channel ID?
1. **Enable Developer Mode:**
   - In Discord, go to `User Settings` > `Advanced`, and turn on `Developer Mode`.

2. **Get Guild ID:**
   - Right-click on your server name and select "Copy Server ID." This is your Guild ID.

3. **Get Channel ID:**
   - Right-click on the channel name and select "Copy Channel ID." This is your Channel ID.

### Issue Format
If you encounter issues, please use the following format to report them:
Your Name:

Issue:

how it happened:

### Need Help
i alone cannot make encryption so i need your help and contributions please to help me
