const wait = require('util').promisify(setTimeout);
const { SlashCommandBuilder } = require('@discordjs/builders');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('ping')
        .setDescription('Replies with Pong!')
        .addStringOption(option => option.setName('input')
            .setDescription('The input to echo back')
            .setRequired(true)
            .addChoice('Funny', 'gif_funny')
            .addChoice('Meme', 'gif_meme')
            .addChoice('Movie', 'gif_movie')),
    async execute(interaction) {
        const string = interaction.options.getString('input');
        await interaction.reply(string);
        await wait(2000);
        await interaction.editReply('Pong again!');
    },
};