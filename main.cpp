#include <Novice.h>
#include <Vector2.h>
#include <ImGuiManager.h>

const char kWindowTitle[] = "LE2B_15_サカモトイクミ";

void lerp(Vector2& Pos, Vector2 StartPos, Vector2 EndPos, float &t) {
	Pos.x = StartPos.x + (EndPos.x - StartPos.x) * t;
	Pos.y = StartPos.y + (EndPos.y - StartPos.y) * t;
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	const int kVerNum = 4;

	bool isMofing = false;

	Vector2 beforePos[kVerNum];
	beforePos[0] = { 10.0f, 10.0f };
	beforePos[1] = { 500.0f, 10.0f };
	beforePos[2] = { 10.0f, 300.0f };
	beforePos[3] = { 500.0f, 300.0f };

	Vector2 afterPos[kVerNum];
	afterPos[0] = { 425.0f, 10.0f };
	afterPos[1] = { 500.0f, 300.0f };
	afterPos[2] = { 10.0f, 300.0f };
	afterPos[3] = { 425.0f, 300.0f };

	
	Vector2 Pos[kVerNum];

	float t = 0.0f;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys [DIK_SPACE]) {
			isMofing = true;
		}
		else if (!keys[DIK_SPACE]) {
			isMofing = false;
		}

		if (isMofing) {

			if (t < 1.0f) {
				t += 0.01f;
			}
			else if (t > 1.0f) {
				t = 1.0f;
			}
		}
		else if (!isMofing) {
			if (t > 0) {
				t -= 0.01f;
			}
			else if (t < 0) {
				t = 0.0f;
			}
		}
		for (int i = 0; i < kVerNum; i++) {
			lerp(Pos[i], beforePos[i], afterPos[i], t);
		}

		ImGui::Begin("Debug");
		ImGui::SliderFloat2("startPos1", &beforePos[0].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("EndPos1", &afterPos[0].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("startPos2", &beforePos[1].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("EndPos2", &afterPos[1].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("startPos3", &beforePos[2].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("EndPos3", &afterPos[2].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("startPos4", &beforePos[3].x, 0.0f, 100.0f);
		ImGui::SliderFloat2("EndPos4", &afterPos[3].x, 0.0f, 100.0f);
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(int(Pos[0].x), int(Pos[0].y), int(Pos[1].x), int(Pos[1].y), WHITE);
		Novice::DrawLine(int(Pos[1].x), int(Pos[1].y), int(Pos[3].x), int(Pos[3].y), WHITE);
		Novice::DrawLine(int(Pos[3].x), int(Pos[3].y), int(Pos[2].x), int(Pos[2].y), WHITE);
		Novice::DrawLine(int(Pos[2].x), int(Pos[2].y), int(Pos[0].x), int(Pos[0].y), WHITE);

		for (int i = 0; i < kVerNum; i++) {
			Novice::ScreenPrintf(int(Pos[i].x) - 20, int(Pos[i].y) + 20, "Vertex:%d", i + 1);
			Novice::DrawEllipse(int(Pos[i].x), int(Pos[i].y), 8, 8, 0.0f, RED, kFillModeSolid);
		}

		///
		/// ↑描画処理ここまで
		///

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
