#include <Novice.h>

enum types {
	ONE,
	TWO,
};

enum gamescene {
	gamestart,
	game,
	result,
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
	int type;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int parea = Novice::LoadTexture("./images/strike.png");
	int scene = gamestart;
	int frame = 0;
	int timer = 0;
	float gravity = 0.5;

	int pAreaX = 700;
	int pAreaY = 400;

	int hitAreaRightX = pAreaX + 32 * 3;
	int hitAreaBottomY = pAreaY + 32 * 3;

	int nowObj = 0;

	int slashNum = 0;

	Obj obj[5] = {
		{{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f},30.0f,WHITE,false,0.0f,ONE},
		{{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f},30.0f,RED,false,0.0f,ONE},
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
			for (int i = 0;i < 5;i++) {
				if (!obj[i].isAlive) {
					nowObj = ((rand() % 2 + 1));
					//リスポーンタイマーが対象秒数になったら
					if (obj[i].respawntime == frame) {
						//オブジェクトを出現させる
						obj[i].isAlive = true;
						//一回切る奴のやつ
						if (obj[i].type == ONE) {
							//オブジェクトの初期化
							obj[i].position.x = 200;
							obj[i].position.y = 200;
							obj[i].velocity.x = 10;
							obj[i].velocity.y = -10.0f;
							//切る回数の初期化
							slashNum = 1;
						}
					}
				}
				else {
					//オブジェクトの物理演算
					obj[i].velocity.y += gravity;
					obj[i].position.x += obj[i].velocity.x;
					obj[i].velocity.y += obj[i].acceleration.y;
					obj[i].position.y += obj[i].velocity.y;
				}
				//スペースを押したとき範囲内なら消す判定
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					if (obj[i].position.x >= pAreaX &&
						obj[i].position.x <= hitAreaRightX &&
						obj[i].position.y >= pAreaY &&
						obj[i].position.y <= hitAreaBottomY)
					{
						//対象物を消す
						obj[i].isAlive = false;
					}
				}
				if (obj[i].position.y >= 720 + obj[i].radius + 20) {
					obj[i].isAlive = false;
				}
			}
			if (!obj[0].isAlive) {
				continue;
			}
		}
		//sceneがgamecreaのとき
		if (scene == result) {

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
			Novice::ScreenPrintf(500, 400, "title");
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = game;
			}
		}
		//sceneがgameのとき
		if (scene == game) {
			Novice::DrawSprite(pAreaX, pAreaY, parea, 3.0f, 3.0f, 0.0f, 0xFFFFFFFF);
			for (int i = 0;i < 5;i++) {
				Novice::DrawEllipse(static_cast<int>(obj[i].position.x), static_cast<int>(obj[i].position.y), static_cast<int>(obj[0].radius), static_cast<int>(obj[i].radius), 0.0f, obj[0].color, kFillModeSolid);
			}
		}
		//sceneがgamecreaのとき
		if (scene == result) {

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
		case result:
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
