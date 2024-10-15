
// LineCode
	std::vector<uint64_t> vas;
	for (int Index = 0; Index < 25; Index++) {
		if (Driver->read<__int32>(Driver->BaseAddress + (Index * 0x1000) + 0x250) == 0x260E020B)
		{
			__int64 va_text = Driver->BaseAddress + ((Index + 1) * 0x1000);
			vas.push_back(Offsets::uWorld + va_text);
		}
	}

	for (uint64_t va : vas) {
		if (Driver->read<UWorld*>(va)) {
			Globals::uWorldAddy = va;
			break;
		}
	}