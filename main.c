#include "stdio.h"
#include <raylib.h>
#include <stdbool.h>

#define RECTCUT_IMPLEMENTATION
#include "rectcut.h"

#include "background.h"
#include "mettaton.h"
#include "frisk.h"
#include "monster_kid_walk.h"
#include "monster_kid_falling.h"

#include "background_music.h"
#include "song.h"
#include "dialog_sound.h"
#include "snd_noise.h"

#define WIDTH 800 
#define HEIGHT 600
#define MESSAGE_LEN 128
#define D1_LEN 71
#define D2_LEN 44
#define D3_LEN 12
#define D4_LEN 103
#define D5_LEN 103
#define D6_LEN 44
#define TEXT_SPEED_DIV 5
#define D3_SPEED_DIV 10
#define FONT_SIZE 32


int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Rectcut test");

    Rect layout = { 0, 0, WIDTH, HEIGHT};
    // layout 800x360
    Rect dialog = cut_bottom(&layout, 240);

    InitAudioDevice();
    Wave song_1_wave = LoadWaveFromMemory(".mp3", background_mp3, background_mp3_len);
    Sound song_1 = LoadSoundFromWave(song_1_wave);

    Wave song_2_wave = LoadWaveFromMemory(".mp3", song_mp3, song_mp3_len);
    Sound song_2 = LoadSoundFromWave(song_2_wave);

    Wave song_3_wave = LoadWaveFromMemory(".wav", snd_noise_wav, snd_noise_wav_len);
    Sound song_3 = LoadSoundFromWave(song_3_wave);

    Wave d1_sound_wave = LoadWaveFromMemory(".wav", dialog_sound_wav, dialog_sound_wav_len);
    Sound d1_sound = LoadSoundFromWave(d1_sound_wave);

    const char d1[D1_LEN] = "And then he said this before he walked out:\nI am nothing like you guys";
    const char d2[D2_LEN] = "Everybody started dying laughing after that";
    const char d3[D3_LEN] = ". . . . . .";
    const char d4[D4_LEN] = "Sigh... look at you fumbling again... Do we really\nhave to carry your ass again?\nWait a second . . .";
    const char d5[D5_LEN] = "You fumbled with 4 legendaries again??\nThis whole time we had shit weapons\nand you had 4 legendaries?";
    const char d6[D6_LEN] = "but bro my teammate I can't do this anymore";
    int dialog_state = 0;

    int text_speed = 0;
    int walk_speed = 3;
    int pause = 0;
    int frame_step_walk = 0;
    int frame_step_fall = 0;
    int frame_step_frisk = 1;
    bool end = false;

    Image background_img = LoadImageFromMemory(".png", background_png, background_png_len);
    Texture2D background = LoadTextureFromImage(background_img);

    Image mettaton_img = LoadImageFromMemory(".png", mettaton_png, mettaton_png_len);
    Texture2D mettaton = LoadTextureFromImage(mettaton_img);

    Image frisk_img = LoadImageFromMemory(".png", frisk_png, frisk_png_len);
    Texture2D frisk = LoadTextureFromImage(frisk_img);

    Image monster_kid_walk_img = LoadImageFromMemory(".png", monster_kid_walk_png, monster_kid_walk_png_len);
    Texture2D monster_kid_walk = LoadTextureFromImage(monster_kid_walk_img);

    Image monster_kid_fall_img = LoadImageFromMemory(".png", monster_kid_falling_png, monster_kid_falling_png_len);
    Texture2D monster_kid_fall = LoadTextureFromImage(monster_kid_fall_img);

    Rectangle frame_frisk = { 0.0f, 0.0f, (float)frisk.width/3, (float)frisk.height };
    Rectangle dest_frisk = {0.0f, 0.0f, (float)frisk.width*2/3, (float)frisk.height*2};

    Rectangle frame_kid_walk = { 0.0f, 0.0f, (float)monster_kid_walk.width/4, (float)monster_kid_walk.height };
    Rectangle dest_kid_walk = {0.0f, 0.0f, (float)monster_kid_walk.width*2/4, (float)monster_kid_walk.height*2};

    Rectangle frame_kid_fall = { 0.0f, 0.0f, (float)monster_kid_fall.width/7, (float)monster_kid_fall.height };
    Rectangle dest_kid_fall = {0, 0, (float)monster_kid_fall.width*2/7, (float)monster_kid_fall.height*2};

    SetTargetFPS((60));
    Vector2 kid_pos = (Vector2){.x = -795, .y = -204};
    Vector2 frisk_pos = (Vector2){.x = -180, .y = -200};
    PlaySound(song_1); 
    while (!WindowShouldClose() && !end)
    {
        text_speed++;
        if (text_speed > 400 && dialog_state == 0) {
            text_speed = 0;
            dialog_state = 1;
        }
        else if (text_speed > 250 && dialog_state == 1) {
            text_speed = 0;
            dialog_state = 2;
        }
        else if (kid_pos.x > -445 && dialog_state == 2) {
            text_speed = 0;
            StopSound(song_1);
            dialog_state = 3;
            kid_pos.x = -395;
        }
        else if (frame_step_fall == 5 && dialog_state == 3) {
            text_speed = 0;
            dialog_state = 4;
            pause = 0;
            PlaySound(song_3);
            frame_kid_fall.x = frame_kid_fall.width * 6;
        }
        else if (pause > 50 && dialog_state == 4) {
            text_speed = 0;
            pause = 0;
            dialog_state = 5;
            frame_frisk.x = frame_frisk.width * 1;
        }
        else if (text_speed > 150 && dialog_state == 5) {
            text_speed = 0;
            dialog_state = 6;
        }
        else if (frisk_pos.x < -360 && dialog_state == 6) {
            PlaySound(song_2);
            text_speed = 0;
            dialog_state = 7;
            pause = 0;
            frame_frisk.x = frame_frisk.width;
        }
        else if (text_speed >= 400 && dialog_state == 7) {
            text_speed = 800;
            dialog_state = 8;
            pause = 0;
        }
        else if (text_speed > 1050 && dialog_state == 8) {
            text_speed = 0;
            dialog_state = 9;
            pause = 0;
        }
        else if (text_speed > 550 && dialog_state == 9) {
            text_speed = 0;
            dialog_state = 10;
            pause = 0;
        }
        else if (text_speed > 450 && dialog_state == 10) {
            text_speed = 0;
            dialog_state = 11;
            pause = 0;
            StopSound(song_2);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(background, layout.min_x, layout.min_y, WHITE);
            DrawTextureEx(mettaton, (Vector2){.x = 150, .y = 175}, 0, 1.5, WHITE);
            DrawRectangleLinesEx((Rectangle) {.x = dialog.min_x, .y = dialog.min_y, .width = dialog.max_x, .height = dialog.max_y - dialog.min_y}, 5, WHITE);
            DrawTexturePro(frisk, frame_frisk, dest_frisk, frisk_pos, 0, WHITE);
            if (dialog_state == 0) {
                if (text_speed % 5 == 0 && text_speed < 366) {
                    PlaySound(d1_sound); 
                }
                DrawText(TextSubtext(d1, 0, text_speed / TEXT_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 1) {
                if (text_speed % 5 == 0 && text_speed < 221) {
                    PlaySound(d1_sound); 
                }
                DrawText(TextSubtext(d2, 0, text_speed / TEXT_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 2) {
                kid_pos.x += walk_speed;
                DrawTexturePro(monster_kid_walk, frame_kid_walk, dest_kid_walk, kid_pos, 0, WHITE);
                frame_step_walk == 4 ? frame_step_walk = 0 : frame_step_walk++;
                frame_kid_walk.x = frame_kid_walk.x + frame_kid_walk.width * frame_step_walk;
            }
            else if (dialog_state == 3) {
                frame_kid_fall.x = frame_kid_fall.x + frame_kid_fall.width * frame_step_fall;
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                frame_step_fall++;
            }
            else if (dialog_state == 4) {
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                pause++;
            }
            else if (dialog_state == 5) {
                if (text_speed % 20 == 0 && text_speed < 120) {
                    PlaySound(d1_sound); 
                }
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                DrawText(TextSubtext(d3, 0, text_speed / D3_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 6) {
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                frisk_pos.x -= (walk_speed - 2);
                if (pause > 10) {
                    frame_step_frisk == 2 ? frame_step_frisk = 1 : frame_step_frisk++;
                    pause = 0;
                } 
                else {
                    pause++;
                }
                frame_frisk.x = frame_frisk.width * frame_step_frisk;
            }
            else if (dialog_state == 7) {
                if (text_speed % 5 == 0 && text_speed < 400) {
                    PlaySound(d1_sound); 
                }
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                DrawText(TextSubtext(d4, 0, text_speed / TEXT_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 8) {
                if (text_speed % 10 == 0 && text_speed < 1030) {
                    PlaySound(d1_sound); 
                }
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                DrawText(TextSubtext(d4, 0, text_speed / D3_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 9) {
                if (text_speed % 5 == 0 && text_speed < 515) {
                    PlaySound(d1_sound); 
                }
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                DrawText(TextSubtext(d5, 0, text_speed / TEXT_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 10) {
                if (text_speed % 10 == 0 && text_speed < 440) {
                    PlaySound(d1_sound); 
                }
                DrawTexturePro(monster_kid_fall, frame_kid_fall, dest_kid_fall, kid_pos, 0, WHITE);
                DrawText(TextSubtext(d6, 0, text_speed / D3_SPEED_DIV), dialog.min_x + FONT_SIZE, dialog.min_y + FONT_SIZE, FONT_SIZE, WHITE);
            }
            else if (dialog_state == 11) {
                end = true;
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
