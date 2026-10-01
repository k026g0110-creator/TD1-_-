#include <Novice.h>

enum types {
	ONE,
	TWO,
};

enum gamescene {
	gamestart,
	game,
	gamecrea,
	gamemiss
};

const char kWindowTitle[] = "LC1B_06_オノザワ_カナト_タイトル";

struct Vector2 {
	float x;
	float y;
};

struct Obj {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float radius;
	unsigned int color;
	bool isAlive;
	float respawntime;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int parea = Novice::LoadTexture("./images/strike.png");
	int scene = game;
	int frame = 0;
	int timer = 0;
	float gravity = 0.5;

	int pAreaX = 700;
	int pAreaY = 400;

	int hitAreaRightX = pAreaX + 32 * 3;
	int hitAreaBottomY = pAreaY + 32 * 3;

	Obj obj[5] = {
		{{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f},30.0f,WHITE,false,0.0f},
	    {{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f},30.0f,RED,false,0.0f},
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		//タイマーとフレーム
		timer++;
		if (timer > 60) {
			timer = 0;
			frame++;
		}
		if (frame > 20) {
			frame = 0;
		}

		///
		/// ↓更新処理ここから
		///

		//sceneがgamestartのとき
		if (scene == gamestart) {

		}
		//sceneがgameのとき
		if (scene == game) {
			//オブジェクトが生きていない
			if (!obj[0].isAlive) {
				//リスポーンタイマーが対象秒数になったら
				if (obj[0].respawntime == frame) {
					//オブジェクトを出現させる
					obj[0].isAlive = true;
					//オブジェクトの初期化
					obj[0].position.x = 200;
					obj[0].position.y = 200;
					obj[0].velocity.x = 10;
					obj[0].velocity.y = -10.0f;
				}
			}
			else {
				//オブジェクトの物理演算
				obj[0].velocity.y += gravity;
				obj[0].position.x += obj[0].velocity.x;
				obj[0].velocity.y += obj[0].acceleration.y;
				obj[0].position.y += obj[0].velocity.y;
			}
			//スペースを押したとき範囲内なら消す判定
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				if (obj[0].position.x >= pAreaX &&
					obj[0].position.x <= hitAreaRightX &&
					obj[0].position.y >= pAreaY &&
					obj[0].position.y <= hitAreaBottomY)
				{
					//対象物を消す
					obj[0].isAlive = false;
				}
			}
			if (!obj[0].isAlive) {
				continue;
			}
		}

		//sceneがgamecreaのとき
		if (scene == gamecrea) {

		}
		//sceneがgamemissのとき
		if (scene == gamemiss) {

		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//sceneがgamestartのとき
		if (scene == gamestart) {

		}
		//sceneがgameのとき
		if (scene == game) {
			Novice::DrawSprite(pAreaX, pAreaY, parea, 3.0f, 3.0f, 0.0f, 0xFFFFFFFF);
			Novice::DrawEllipse(static_cast<int>(obj[0].position.x), static_cast<int>(obj[0].position.y), static_cast<int>(obj[0].radius), static_cast<int>(obj[0].radius), 0.0f, obj[0].color, kFillModeSolid);
		}
		//sceneがgamecreaのとき
		if (scene == gamecrea) {

		}
		//sceneがgamemissのとき
		if (scene == gamemiss) {

		}

		///
		/// ↑描画処理ここまで
		///
		switch (scene) {
		case gamestart:
			break;
		case game:
			break;
		case gamecrea:
			break;
		case gamemiss:
			break;
		}
		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
