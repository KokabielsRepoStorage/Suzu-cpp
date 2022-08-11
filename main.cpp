//Include statement
#include <iostream>
#include<String>
#include <Array>
#include "sleepy_discord/sleepy_discord.h"
#include "include/bot-details.h"

//Using statements
using std::string;
using std::cout;
using std::endl;

string names[2] = { "ping", " "};
string description[1] = { "Replies ping!" };

//The client class
class MyClientClass : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message) override {
		if (message.startsWith(".")) {
			string msg = message.content;
			msg.erase(remove(msg.begin(), msg.end(), '.'), msg.end());

			cout << msg << endl;

			if (msg.rfind("ping", 5) == 0) {
				sendMessage(message.channelID, "Pong!!");
			}

			if (msg.rfind("help", 4) == 0) {
				SleepyDiscord::Embed embed{};

				embed.title = "Help embed";
				embed.url = "https://github.com/suzzudev/Suzu-Cpp";
				embed.fields = { SleepyDiscord::EmbedField("Interaction commands", "Ping, help"), SleepyDiscord::EmbedField("Message Commands", "Ping"), SleepyDiscord::EmbedField("Github Link", "https://github.com/SuzzuDev/Suzu") };
				embed.description = "This is the cpp version. Js is the github link.";
				sendMessage(message.channelID, "Help embed", embed);
			}
		}
	}

	void onReady(SleepyDiscord::Ready ready) {
		cout << "Client ready as " + ready.user.username + "~" << endl;

		for (int i = 0; !(names[i] == " "); i++) {
			SleepyDiscord::DiscordClient::createGlobalAppCommand(SleepyDiscord::DiscordClient::BaseDiscordClient::getID(), names[i], description[i]);
			SleepyDiscord::DiscordClient::createAppCommand(SleepyDiscord::DiscordClient::BaseDiscordClient::getID(), "967117817663074304", names[i], description[i]);

		}
	}	

	void onInteraction(SleepyDiscord::Interaction interaction) override {
		if (interaction.data.name == "ping") {
			SleepyDiscord::Interaction::Response<> response;
			response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
			response.data.content = "pong!";
			createInteractionResponse(interaction.ID, interaction.token, response);
		} if (interaction.data.name == "help") {
			SleepyDiscord::Interaction::Response<> response;
			response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
			SleepyDiscord::Embed embed{};
			embed.title = "Help embed";
			embed.url = "https://github.com/suzzudev/Suzu-Cpp";
			embed.fields = { SleepyDiscord::EmbedField("Interaction commands", "Ping, help"), SleepyDiscord::EmbedField("Message Commands", "Ping"), SleepyDiscord::EmbedField("Github Link", "https://github.com/SuzzuDev/Suzu") };
			embed.description = "This is the cpp version. Js is the github link.";
			response.data.embeds = { embed };
			response.data.content = "Help embed";

			createInteractionResponse(interaction.ID, interaction.token, response);
		}
		else {
			//not found
			SleepyDiscord::Interaction::Response<> response;
			response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
			response.data.content = "Couldn't find command";
			response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
			createInteractionResponse(interaction, interaction.token, response);
			return;
		}
	}

};

//Main class
int main() {
	MyClientClass client(TOKEN, SleepyDiscord::USER_CONTROLED_THREADS);
	client.setIntents(SleepyDiscord::Intent::SERVER_MESSAGES);
	client.run();
}