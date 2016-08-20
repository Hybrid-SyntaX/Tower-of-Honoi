void RenderScene(void);
void InitializeScene();
void WindowsSizeChangedEvent(int width,int height);

void SpecialKeyDownEvent(int key,int x,int y);
void Animate(int value);
void RenderTowers();
void SolveTower();

void InitializeTowers();

void SelectTower( Tower & tower);
//void SelectTower( auto_ptr<Tower> tower);
//void SelectTower( auto_ptr_ref<Tower> tower);

