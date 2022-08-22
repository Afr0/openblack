/*****************************************************************************
 * Copyright (c) 2018-2021 openblack developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/openblack/openblack
 *
 * openblack is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "CameraPath.h"

#include "CamFile.h"
#include "ECS/Registry.h"
#include "Game.h"

using namespace openblack;

CameraPath::CameraPath(std::string debugName)
    : _debugName(std::move(debugName))
    , _movementSpeed(0)
    , _start(entt::null)
    , _unk1(0)
{
}

bool CameraPath::LoadFromFile(const std::filesystem::path& path)
{
	cam::CamFile file;
	file.Open(path.string());
	auto filePoints = file.GetPoints();

	for (auto& filePoint : filePoints)
	{
		auto& node = _points.emplace_back();
		node.start = _points.size() == 1;
		node.position = filePoint.position;
		node.rotation = filePoint.lookAtPosition;
	}

	_movementSpeed = file.GetMovementSpeed();
	_unk1 = file.GetUnknown1();
	return true;
}
