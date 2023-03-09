project(GameLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h GameView.cpp GameView.h Game.cpp Game.h Item.cpp Item.h Money.cpp Money.h Platform.cpp Platform.h Scoreboard.cpp Scoreboard.h SpartyGnome.cpp SpartyGnome.h Timer.cpp Timer.h TuitionUp.cpp TuitionUp.h Villain.cpp Villain.h Door.cpp Door.h ids.h ItemBackground.cpp ItemBackground.h Wall.cpp Wall.h Vector.cpp Vector.h Picture.cpp Picture.h GameLevel.cpp GameLevel.h ItemVisitor.cpp ItemVisitor.h RareCandy.cpp RareCandy.h ObstacleVisitor.cpp ObstacleVisitor.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Using precompiled headers
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)