#include "chapters/unlock.h"

static bool p_readUnlockFileKeyword(const uint64_t keyword, FILE* unlockFile)
{
	uint64_t entry = 0;

	if(fread(&entry, sizeof(uint64_t), 1, unlockFile) == EOF) return true;

	return entry == keyword;
}

static void p_writeKeyword(const uint64_t keyword)
{
	FILE* file = fopen("unlock", "a");

	if(file == NULL) return;

	fwrite(&keyword, sizeof(uint64_t), 1, file);

	fclose(file);
}

static void p_readUnlockFile(uint32_t* minigameOn, uint32_t* chapterOn)
{
	const uint64_t minigameKeyword0 = MMS_MMS0MinigameKeyword();
	const uint64_t keyword1 = MMS_MMS1Keyword();

	const uint64_t minigameKeyword1 = MMS_MMS1MinigameKeyword();
	const uint64_t keyword2 = MMS_MMS2Keyword();

	const uint64_t minigameKeyword2 = MMS_MMS2MinigameKeyword();
	const uint64_t keyword3 = MMS_MMS3Keyword();

	FILE* unlockFile = fopen("unlock", "r");

	*minigameOn = 0;
	*chapterOn = 0;

	if(unlockFile == NULL) return;

	if(p_readUnlockFileKeyword(minigameKeyword0, unlockFile)) *minigameOn = 1;
	else
	{
		fclose(unlockFile);
		return;
	}

	if(p_readUnlockFileKeyword(keyword1, unlockFile)) *chapterOn = 1;
	else
	{
		fclose(unlockFile);
		return;
	}

	if(p_readUnlockFileKeyword(minigameKeyword1, unlockFile)) *minigameOn = 2;
	else
	{
		fclose(unlockFile);
		return;
	}

	if(p_readUnlockFileKeyword(keyword2, unlockFile)) *chapterOn = 2;
	else
	{
		fclose(unlockFile);
		return;
	}

	if(p_readUnlockFileKeyword(minigameKeyword2, unlockFile)) *minigameOn = 3;
	else
	{
		fclose(unlockFile);
		return;
	}

	if(p_readUnlockFileKeyword(keyword3, unlockFile)) *chapterOn = 3;
	else
	{
		fclose(unlockFile);
		return;
	}

	fclose(unlockFile);
}

static void p_createUnlockFile()
{
	FILE* unlockFile = fopen("unlock", "r");

	if(unlockFile != NULL)
	{
		fclose(unlockFile);
		return;
	}

	unlockFile = fopen("unlock", "w+");

	if(unlockFile == NULL)
	{
		fclose(unlockFile);
		//  error
		return;
	}

	p_writeKeyword(MMS_MMS0MinigameKeyword()); // < file should unlock the minigame on creation

	fclose(unlockFile);
}

uint64_t MMS_MMS0MinigameKeyword()
{
	static const uint8_t codeWord[8] = { 'D', 'A', 'G', 'M', 'A', 'R', 'K', '!' };

	return *(uint64_t*)codeWord;
}

uint64_t MMS_MMS1Keyword()
{
	static const uint8_t codeWord[8] = { 'M', 'O', 'R', 'M', 'O', 'N', '1', '3' };

	return *(uint64_t*)codeWord;
}

uint64_t MMS_MMS1MinigameKeyword()
{
	static const uint8_t codeWord[8] = { 'D', 'O', 'G', 'O', 'R', 'C', 'A', 'T' };

	return *(uint64_t*)codeWord;
}

uint64_t MMS_MMS2Keyword()
{
	static const uint8_t codeWord[8] = { 123, '6', '9', '6', 69, '6', 'X', 6 };

	return *(uint64_t*)codeWord;
}

uint64_t MMS_MMS2MinigameKeyword()
{
	static const uint8_t codeWord[8] = { 'E', 'G', 'A', 'D', 'S', 128, 130, '!' };

	return *(uint64_t*)codeWord;
}

uint64_t MMS_MMS3Keyword()
{
	static const uint8_t codeWord[8] = { 8, 16, 32, 64, 128, 1, 3, 7 };

	return *(uint64_t*)codeWord;
}

bool MMS_MMS0MinigameUnlocked()
{
	uint32_t minigameOn = 0;
	uint32_t chapterOn = 0;

	p_readUnlockFile(&minigameOn, &chapterOn);

	return minigameOn > 0;
}

bool MMS_MMS1Unlocked()
{
	uint32_t minigameOn = 0;
	uint32_t chapterOn = 0;

	p_readUnlockFile(&minigameOn, &chapterOn);

	return chapterOn > 0;
}

bool MMS_MMS1MinigameUnlocked()
{
	uint32_t minigameOn = 0;
	uint32_t chapterOn = 0;

	p_readUnlockFile(&minigameOn, &chapterOn);

	return minigameOn > 1;
}

bool MMS_MMS2Unlocked()
{
	uint32_t minigameOn = 0;
	uint32_t chapterOn = 0;

	p_readUnlockFile(&minigameOn, &chapterOn);

	return chapterOn > 1;
}

bool MMS_MMS2MinigameUnlocked()
{
	uint32_t minigameOn = 0;
	uint32_t chapterOn = 0;

	p_readUnlockFile(&minigameOn, &chapterOn);

	return minigameOn > 2;
}

bool MMS_MMS3Unlocked()
{
	uint32_t minigameOn = 0;
	uint32_t chapterOn = 0;

	p_readUnlockFile(&minigameOn, &chapterOn);

	return chapterOn > 2;
}

void MMS_MMS0MarkMinigame()
{
	if(MMS_MMS0MinigameUnlocked()) return;

	p_createUnlockFile(); // < already unlocks minigame0
}

void MMS_MMS0MarkEnd()
{
	if(MMS_MMS1Unlocked()) return;

	p_writeKeyword(MMS_MMS1Keyword());
}

void MMS_MMS1MarkMinigame()
{
	if(MMS_MMS1MinigameUnlocked()) return;

	p_writeKeyword(MMS_MMS1MinigameKeyword());
}

void MMS_MMS1MarkEnd()
{
	if(MMS_MMS2Unlocked()) return;

	p_writeKeyword(MMS_MMS2Keyword());
}

void MMS_MMS2MarkMinigame()
{
	if(MMS_MMS2MinigameUnlocked()) return;

	p_writeKeyword(MMS_MMS2MinigameKeyword());
}

void MMS_MMS2MarkEnd()
{
	if(MMS_MMS3Unlocked()) return;

	p_writeKeyword(MMS_MMS3Keyword());
}
