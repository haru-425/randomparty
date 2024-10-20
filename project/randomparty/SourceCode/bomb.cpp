#include "all.h"

// 爆弾の情報を保持する構造体
BombInfo bomb_def;         // デフォルトの爆弾情報
BombInfo stage[BOMB_MAX];  // 各ステージに存在する爆弾情報を保持
int player_has_bomb;       // プレイヤーが持っている爆弾の数

// 通常の爆弾の定義（爆弾番号、プレイヤー攻撃フラグ、爆風範囲、時間、爆弾の有効性）
BombInfo normal = { 0, 1, 3.0, 2, true };

// スプライト（爆弾の画像、範囲の画像）
Sprite* range_circl;   // 爆風範囲のスプライト
Sprite* bomb;          // 爆弾のスプライト

// 外部変数の宣言（プレイヤー、敵、スコア）
extern PLAYER player;
extern ENEMY enemy[ENEMY_MAX];
extern SCORE score;

float remainingAlpha;  // スプライトの透明度を管理するための変数
extern POINT point;    // 外部で定義された座標を保持するPOINT構造体

// 爆弾の初期化処理
void bomb_init()
{
    // デフォルトの爆弾情報を設定
    bomb_def.bomb_number = 0;             // 爆弾番号を 0 に設定（未使用状態）
    bomb_def.bomb_playerattack = false;   // プレイヤーによる攻撃ではない
    bomb_def.bomb_range = 0;              // 爆風の範囲を 0 に設定
    bomb_def.bomb_time = -1;              // タイマーを未設定にする (-1)
    bomb_def.bomb_type = 0;               // 爆弾の種類を 0 に設定
    bomb_def.bomb_position.x = -200;      // 爆弾の位置を初期化 (x = -200)
    bomb_def.bomb_position.y = -200;      // 爆弾の位置を初期化 (y = -200)
    bomb_def.bomb_explode_count = 0;      // 爆発カウントを 0 に設定

    // BOMB_MAX 個の爆弾ステージの初期化（すべてデフォルト値に設定）
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def; // 各爆弾をデフォルトの設定にする
    }

    // スプライトの読み込み
    range_circl = sprite_load(L"./Data/Images/trackingRange.png");  // 爆風範囲のスプライト
    bomb = sprite_load(L"./Data/Images/bomb.png");                 // 爆弾スプライト
    player_has_bomb = BOMB_MAX; // プレイヤーが持っている爆弾の最大数を設定
}

// プレイヤーが爆弾を設置する処理
void bomb_set()
{
    if (player_has_bomb > 0) // プレイヤーが爆弾を持っているかを確認
    {
        // BOMB_MAX 個のスロットから空いている場所を探す
        for (int i = 0; i < BOMB_MAX; i++)
        {
            if (stage[i].bomb_number == 0) // 使われていないスロットを発見
            {
                stage[i] = normal;                  // 新しい爆弾（normal）を設定
                stage[i].bomb_number = i + 1;       // 爆弾番号を設定
                stage[i].bomb_position = player.position; // 爆弾の位置をプレイヤーの現在位置に設定
                break;
            }
        }
        player_has_bomb--; // プレイヤーの持っている爆弾数を減少させる

        sound::play(XWB_SYSTEM, XWB_SYSTEM_BOMB_SET); // 爆弾設置音を再生
    }
    else
    {
        sound::play(XWB_SYSTEM, XWB_SYSTEM_BOMB_FAILURE); // 爆弾設置失敗音を再生
    }
}

// 爆弾のタイマーを更新する処理
void bomb_update()
{
    // すべての爆弾をチェック
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i].bomb_explode_count++; // 爆発カウントをインクリメント

        if (stage[i].bomb_number != 0) // 使われている爆弾のみ処理
        {
            if (stage[i].bomb_explode_count % 60 == 0) // 60フレームごとに
            {
                stage[i].bomb_time -= 1; // タイマーをデクリメント
                if (stage[i].bomb_time == 0) // タイマーが 0 になったら
                {
                    bomb_explosion(i); // 爆発処理を呼び出す

                    sound::play(XWB_SYSTEM, XWB_SYSTEM_EXPLODE); // 爆発音を再生
                }
            }
        }
    }

    // プレイヤーの位置に基づいてスプライトの透明度を設定
    if ((player.position.x - (SCREEN_W - 70)) * (player.position.x - (SCREEN_W - 70)) + (player.position.y - (SCREEN_H - 70)) * (player.position.y - (SCREEN_H - 70)) <= 200 * 200)
    {
        remainingAlpha = 0.5f; // プレイヤーが範囲内なら透明度を変更
    }
    else
    {
        remainingAlpha = 1; // 通常の透明度に戻す
    }
}

// 爆弾の爆発処理
void bomb_explosion(int bomb_number)
{
    int waitTime = 1; // 敵がリポップするまでの待機時間を設定
    float enemy_r = ENEMY_CORE_TEX_W * enemy[0].scale.x / 2; // 敵の半径を計算

    // すべての敵に対してヒット判定を行う
    for (int i = 0; i < ENEMY_MAX; i++)
    {
        // 爆弾の爆発範囲と敵の位置が重なっているかをチェック
        if (circle_hit(stage[bomb_number].bomb_position, enemy[i].position, BOMB_RANGE_SCALE * stage[bomb_number].bomb_range, enemy_r))
        {
            enemy[i].reset();             // 敵のリセット（リポップ処理）
            enemy[i].waitNum = waitTime;   // リポップまでの待機時間を設定
            waitTime++;                    // 次の敵の待機時間を増加

            // スコア追加処理（スコア処理は別途実装）
            score.enemy_kill_point();
        }
    }

    // 爆発が終わったら、爆弾を初期状態に戻す
    stage[bomb_number] = bomb_def;
}

// 爆弾の描画処理
void bomb_render()
{
    for (int i = 0; i < BOMB_MAX; i++)
    {
        // 爆風の範囲を描画
        sprite_render(range_circl, stage[i].bomb_position.x, stage[i].bomb_position.y, SCALE * stage[i].bomb_range * 2, SCALE * stage[i].bomb_range * 2, 0, 0, 400, 400, 200, 200, 0, 1, 0, 0);

        // 爆弾本体を描画
        sprite_render(bomb, stage[i].bomb_position.x, stage[i].bomb_position.y, SCALE * stage[i].bomb_range * 0.5, SCALE * stage[i].bomb_range * 0.5, 0, 0, 400, 400, 200, 200, 0);

        // 爆弾の残り時間を描画
        std::string bomb_time = std::to_string(stage[i].bomb_time);
        text_out(1, bomb_time.c_str(), stage[i].bomb_position.x - 17, stage[i].bomb_position.y - 12, 1, 1, 1, 1, 1, 1);  // 爆弾の位置にタイマーを描画
    }

    // 爆弾のアイコンを描画
    sprite_render(bomb, SCREEN_W - 70, SCREEN_H - 70, 0.5f, 0.5f, 1, 1, 400, 400, 200, 200, 0, 1, 1, 1, remainingAlpha);

    // プレイヤーが持っている爆弾数を描画
    text_out(1, std::to_string(player_has_bomb), SCREEN_W - 40, SCREEN_H - 40, 2, 2, 1, 1, 1, remainingAlpha, TEXT_ALIGN::MIDDLE);
}

// 爆弾のリセット処理
void bomb_deinit()
{
    // すべての爆弾をデフォルト状態にリセット
    for (int i = 0; i < BOMB_MAX; i++)
    {
        stage[i] = bomb_def;
    }

    // スプライトを安全に削除
    safe_delete(range_circl);
    safe_delete(bomb);
}