// There is a lot of reading files
const fs = require('fs');

// needed imports for registering commands
const { REST } = require('@discordjs/rest');
const { Routes } = require('discord-api-types/v9');

// Get the client id and the token
const CLIENT_ID = fs.readFileSync('./clientID.txt', { encoding:'utf8', flag:'r' });
const token = fs.readFileSync('./token.txt', { encoding:'utf8', flag:'r' });

// common for discord API
const { Client, Intents, Collection } = require('discord.js');

// start a new client
const client = new Client({ intents: [Intents.FLAGS.GUILDS] });
// will hold all client commands imported from commadns dir
client.commands = new Collection();

// temporarily stores the commands imported from commands dir
const commands = [];
const commandFiles = fs.readdirSync('./commands').filter(file => file.endsWith('.js'));

// imports all the commands
for (const file of commandFiles) {
    const command = require(`./commands/${file}`);
    client.commands.set(command.data.name, command);
    commands.push(command.data.toJSON());
}

const rest = new REST({ version: '9' }).setToken(token);

client.once('ready', () => {

    // when the bot starts it will register all the commands for the servers that it is in
    // For production this should be using applicationCommands with the clientID but that will only
    // update the commands every hour instead of instantly which is needed for development
    client.guilds.cache.each(guild => {
        (async () => {
            try {
                console.log('Started refreshing application (/) commands.');

                await rest.put(
                    Routes.applicationGuildCommands(CLIENT_ID, guild.id),
                    { body: commands },
                );

                console.log('Successfully reloaded application (/) commands.');
            }
            catch (error) {
                console.error(error);
            }
        })();
    });
});

client.on('interactionCreate', async interaction => {
    if (!interaction.isCommand()) return;

    // if we have the command then execute it
    if (!client.commands.has(interaction.commandName)) return;

    try {
        await client.commands.get(interaction.commandName).execute(interaction);
    }
    catch (error) {
        console.error(error);
        await interaction.reply({ content: 'There was an error while executing this command!', ephemeral: true });
    }
});

// start the client
client.login(token);

// for gracefully shutting down the client using ctlr + c
process.on('SIGINT', function() {
    console.log('Gracefully shutting down application');
    process.exit(1);
});