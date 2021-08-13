const Canvas = require('canvas');
const wait = require('util').promisify(setTimeout);
const { SlashCommandBuilder } = require('@discordjs/builders');
const { MessageAttachment, MessageButton, MessageActionRow } = require('discord.js');

/**
 * Each person can only see their instance of the game
 */
module.exports = {
    data: new SlashCommandBuilder()
        .setName('profile')
        .setDescription('Show profile pic'),
    async execute(interaction) {
        const canvas = Canvas.createCanvas(700, 500);
        const context = canvas.getContext('2d');
        // Since the image takes time to load, you should await it
        let background = await Canvas.loadImage('./wallpaper.jpg');

        // This uses the canvas dimensions to stretch the image onto the entire canvas
        context.drawImage(background, 0, 0, canvas.width, canvas.height);
        const avatar = await Canvas.loadImage(interaction.user.displayAvatarURL({ format: 'jpg' }));
        context.drawImage(avatar, 25, 0, 200, canvas.height);
        // Use the helpful Attachment class structure to process the file for you
        let attachment = new MessageAttachment(canvas.toBuffer(), 'profile-image.png');

        const row = new MessageActionRow()
            .addComponents(
                new MessageButton()
                    .setCustomId('primary')
                    .setLabel('Primary')
                    .setStyle('PRIMARY'),
            );


        await interaction.reply({ files: [attachment], components: [row] });
        await wait(2000);
        background = await Canvas.loadImage('./wallpaper2.jpg');
        context.drawImage(background, 0, 0, canvas.width, canvas.height);
        context.drawImage(avatar, 25, 0, 200, canvas.height);

        attachment = new MessageAttachment(canvas.toBuffer(), 'profile-image.png');
        await interaction.editReply({ files: [attachment], components: [row] });
    },
};