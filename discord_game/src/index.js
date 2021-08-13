const fs = require('fs');
const { REST } = require('@discordjs/rest');
const { Routes } = require('discord-api-types/v9');
const CLIENT_ID = fs.readFileSync('./clientID.txt', { encoding:'utf8', flag:'r' });
const token = fs.readFileSync('./token.txt', { encoding:'utf8', flag:'r' });

const { Client, Intents, Collection } = require('discord.js');

const client = new Client({ intents: [Intents.FLAGS.GUILDS] });
client.commands = new Collection();
const commands = [];
const commandFiles = fs.readdirSync('./commands').filter(file => file.endsWith('.js'));

for (const file of commandFiles) {
    const command = require(`./commands/${file}`);
    client.commands.set(command.data.name, command);
    commands.push(command.data.toJSON());
}

const rest = new REST({ version: '9' }).setToken(token);

client.once('ready', () => {
    console.log(CLIENT_ID);
    client.guilds.cache.each(guild => {
        // when the bot starts it will register all the commands for the servers that it is in
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

    if (!client.commands.has(interaction.commandName)) return;

    try {
        await client.commands.get(interaction.commandName).execute(interaction);
    }
    catch (error) {
        console.error(error);
        await interaction.reply({ content: 'There was an error while executing this command!', ephemeral: true });
    }
});


client.login(token);

process.on('SIGINT', function() {
    console.log('Gracefully shutting down application');
    // some other closing procedures go here
    process.exit(1);
});