#include "utility/defaults.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	PLEX_FAKESTRING_100 name;
	PLEX_FAKESTRING_500 comment;
	PLEX_DEF_ENTRYTYPE type;
	double min, max, def;
} P_DEFAULTENTRY;

// static values ------------------------------------------------------------------------------------------------------------

// default defaults (ie. what defaults are if they don't load from config)

static const uint32_t p_minWidth = 800;
static const uint32_t p_maxWidth = 4096;

static const uint32_t p_minHeight = 600;
static const uint32_t p_maxHeight = 2160;

static const uint32_t p_defWidth = 800;
static const uint32_t p_defHeight = 600;

static const uint8_t p_defCursorR = 255;
static const uint8_t p_defCursorG = 0;
static const uint8_t p_defCursorB = 0;

static const double p_defCursorW = 1;
static const double p_defCursorH = 1;

static const bool p_defKillOnEscape = true;
static const bool p_defKillOnClose = true;

static const bool p_defAllowResize = true;
static const bool p_defAllowMaximize = true;
static const bool p_defStartMaximize = false;

static const bool p_defDisableSound = false;

static const bool p_defDisableController = false;
static const bool p_defDisableJoystick = false;
static const bool p_defDisableKeyboard = false;
static const bool p_defDisableMouse = false;

static const bool p_defControllerPause = true;

static const bool p_def42Hour = false;

static const uint32_t p_defTextureDimensLimit = 10000;

static const bool p_defPrintErrors = true;
static const bool p_defShowErrors = true;
static const bool p_defDumpErrors = false;

static const uint8_t p_defPrintErrorThreshhold = 4;
static const uint8_t p_defShowErrorThreshold = 3;
static const uint8_t p_defFatalErrorThreshold = 2;

static const bool p_defHeaderlessCopy = true;

static const uint8_t p_defMemoryProfile = 0;

static const bool p_defMemoryReport = false;
static const bool p_defMemoryReportToFile = true;

// the index values of the defaults

static int64_t p_width = -1;
static int64_t p_height = -1;

static int64_t p_killOnEscape = -1;
static int64_t p_killOnClose = -1;

static int64_t p_allowResize = -1;
static int64_t p_allowMaximize = -1;
static int64_t p_startMaximized = -1;

static int64_t p_disableSound = -1;

static int64_t p_disableController = -1;
static int64_t p_disableJoystick = -1;
static int64_t p_disableKeyboard = -1;
static int64_t p_disableMouse = -1;

static int64_t p_cursorR = -1;
static int64_t p_cursorG = -1;
static int64_t p_cursorB = -1;

static int64_t p_cursorW = -1;
static int64_t p_cursorH = -1;

static int64_t p_controllerPause = -1;

static int64_t p_24hourTime = -1;

static int64_t p_textureDimensLimit = -1;

static int64_t p_printErrors = -1;
static int64_t p_showErrors = -1;
static int64_t p_dumpErrors = -1;

static int64_t p_printErrorThreshold = -1;
static int64_t p_showErrorThreshold = -1;
static int64_t p_fatalErrorThreshold = -1;

static int64_t p_headerlessCopy = -1;

static int64_t p_memoryProfile = -1;

static int64_t p_memReport = -1;
static int64_t p_memReportToFile = -1;

// the internal collection of entries

static PLEX_EXPANDARRAY* p_entries = NULL;

// where the string entires are stored

static PLEX_STRINGBANK* p_stringBank = NULL;

static bool p_running = false;

// static functions ---------------------------------------------------------------------------------------------------------

// ensures that default is within a minimum and maximum

static double p_validateNumberDefault(const double min, const double max, const double def)
{
	if(def < min) return min;
	if(def > max) return max;

	return def;
}

// generates a default entry

static P_DEFAULTENTRY p_genDefault(const char* const name, const PLEX_DEF_ENTRYTYPE type, const double min, const double max, const double def, const char* comment, const size_t errorline, const char* const errorfile)
{
	P_DEFAULTENTRY ret;

	ret.name = PLEX_createString100Int(name, errorline, errorfile);
	ret.comment = PLEX_blankString500Int(errorline, errorfile);
	ret.type = type;
	ret.min = min;
	ret.max = max;
	ret.def = def;

	if(comment != NULL) ret.comment = PLEX_createString500Int(comment, errorline, errorfile);

	return ret;
}

// sets particular default's name'

static int64_t p_assignDefault(const char* const name, const PLEX_DEF_ENTRYTYPE type, const double min, const double max, const double def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	size_t entryCount = 0;

	P_DEFAULTENTRY* entry = NULL;

	entryCount = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

	for(size_t ze = 0; ze < entryCount; ++ze)
	{
		PLEX_FAKESTRING_100 entryName = PLEX_createString100Int(name, errorline, errorfile);

		P_DEFAULTENTRY* entry2 = PLEX_getExpandArrayEntryInt(ze, p_entries, errorline, errorfile);

		if(entry2 == NULL) PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONASSIGN, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);

		if(PLEX_compStrings100Int(entryName, entry2->name, true, errorline, errorfile))
		{
			entry2->type = type;

			entry2->min = min;
			entry2->max = max;
			entry2->def = def;

			entry2->comment = PLEX_createString500Int(comment, errorline, errorfile);

			return ze;
		}
	}

	if(!PLEX_incrementExpandArrayInt(p_entries, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONASSIGN, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return -1;
	}

	entry = (P_DEFAULTENTRY*)PLEX_getExpandArrayLastInt(p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONASSIGN, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return -1;
	}

	*entry = p_genDefault(name, type, min, max, def, comment, errorline, errorfile);

	return PLEX_expandArrayCountInt(p_entries, errorline, errorfile) - 1;
}

// populates all the defaults

static void p_populateDefaults(const size_t errorline, const char* const errorfile)
{
	PLEX_clearExpandArrayInt(p_entries, errorline, errorfile);

	p_width = PLEX_assignDefaultUInt32Int(PLEX_DEFNAME_MAINWINWIDTH, p_minWidth, p_maxWidth, p_defWidth, PLEX_DEFDESC_MAINWINWIDTH, errorline, errorfile);
	p_height = PLEX_assignDefaultUInt32Int(PLEX_DEFNAME_MAINWINHEIGHT, p_minHeight, p_maxHeight, p_defHeight, PLEX_DEFDESC_MAINWINHEIGHT, errorline, errorfile);

	p_killOnEscape = PLEX_assignDefaultBoolInt(PLEX_DEFNAME_KILLONESCAPE, p_defKillOnEscape, PLEX_DEFDESC_KILLONESCAPE, errorline, errorfile);
	p_killOnClose = PLEX_assignDefaultBoolInt(PLEX_DEFNAME_KILLONCLOSE, p_defKillOnClose, PLEX_DEFDESC_KILLONCLOSE, errorline, errorfile);

	p_allowResize = PLEX_assignDefaultBoolInt(PLEX_DEFNAME_ALLOWRESIZE, p_defAllowResize, PLEX_DEFDESC_ALLOWRESIZE, errorline, errorfile);
	p_allowMaximize = PLEX_assignDefaultBoolInt(PLEX_DEFNAME_ALLOWMAXIMIZE, p_defAllowMaximize, PLEX_DEFDESC_ALLOWMAXIMIZE, errorline, errorfile);
	p_startMaximized = PLEX_assignDefaultBoolInt(PLEX_DEFNAME_STARTMAXIMIZED, p_defStartMaximize, PLEX_DEFDESC_STARTMAXIMIZED, errorline, errorfile);

	p_disableSound = PLEX_assignDefaultBoolInt(PLEX_DEFNAME_DISABLESOUND, p_defDisableSound, PLEX_DEFDESC_DISABLESOUND, errorline, errorfile);

	p_cursorR = PLEX_assignDefaultUInt8Int(PLEX_DEFNAME_CURSOR_R, 0, 255, p_defCursorR, PLEX_DEFDESC_CURSOR_R, errorline, errorfile);
	p_cursorG = PLEX_assignDefaultUInt8Int(PLEX_DEFNAME_CURSOR_G, 0, 255, p_defCursorG, PLEX_DEFDESC_CURSOR_G, errorline, errorfile);
	p_cursorB = PLEX_assignDefaultUInt8Int(PLEX_DEFNAME_CURSOR_B, 0, 255, p_defCursorB, PLEX_DEFDESC_CURSOR_B, errorline, errorfile);

	p_cursorW = PLEX_assignDefaultDoubleInt(PLEX_DEFNAME_CURSOR_W, 0.1, 2, p_defCursorW, PLEX_DEFDESC_CURSOR_W, errorline, errorfile);
	p_cursorH = PLEX_assignDefaultDoubleInt(PLEX_DEFNAME_CURSOR_H, 0.1, 2, p_defCursorH, PLEX_DEFDESC_CURSOR_H, errorline, errorfile);

	p_controllerPause = PLEX_assignDefaultBool(PLEX_DEFNAME_CONTROLLERPAUSE, p_defControllerPause, PLEX_DEFDESC_CONTROLLERPAUSE);

	p_disableController = PLEX_assignDefaultBool(PLEX_DEFNAME_DISABLECONTROLLER, p_defDisableController, PLEX_DEFDESC_DISABLECONTROLLER);
	p_disableJoystick = PLEX_assignDefaultBool(PLEX_DEFNAME_DISABLEJOYSTICK, p_defDisableJoystick, PLEX_DEFDESC_DISABLEJOYSTICK);
	p_disableKeyboard = PLEX_assignDefaultBool(PLEX_DEFNAME_DISABLEKEYBOARD, p_defDisableKeyboard, PLEX_DEFDESC_DISABLEKEYBOARD);
	p_disableMouse = PLEX_assignDefaultBool(PLEX_DEFNAME_DISABLEMOUSE, p_defDisableMouse, PLEX_DEFDESC_DISABLEMOUSE);

	p_24hourTime = PLEX_assignDefaultBool(PLEX_DEFNAME_24HOURTIME, p_def42Hour, PLEX_DEFDESC_24HOURTIME);

	p_textureDimensLimit = PLEX_assignDefaultUInt32(PLEX_DEFNAME_TEXTUREDIMENSLIMIT, 1024, 99999, p_defTextureDimensLimit, PLEX_DEFDESC_TEXTUREDIMENSLIMIT);

	p_printErrors = PLEX_assignDefaultBool(PLEX_DEFNAME_PRINTERRORS, p_defPrintErrors, PLEX_DEFDESC_PRINTERRORS);
	p_showErrors = PLEX_assignDefaultBool(PLEX_DEFNAME_SHOWERRORS, p_defShowErrors, PLEX_DEFDESC_SHOWERRORS);
	p_dumpErrors = PLEX_assignDefaultBool(PLEX_DEFNAME_DUMPERRORS, p_defDumpErrors, PLEX_DEFDESC_DUMPERRORS);

	p_printErrorThreshold = PLEX_assignDefaultUInt8(PLEX_DEFNAME_PRINTTHRESHOLD, 1, 5, p_defPrintErrorThreshhold, PLEX_DEFDESC_PRINTTHRESHOLD);
	p_showErrorThreshold = PLEX_assignDefaultUInt8(PLEX_DEFNAME_SHOWTHRESHOLD, 1, 5, p_defShowErrorThreshold, PLEX_DEFDESC_SHOWTHRESHOLD);
	p_fatalErrorThreshold = PLEX_assignDefaultUInt8(PLEX_DEFNAME_FATALTHRESHOLD, 2, 5, p_defFatalErrorThreshold, PLEX_DEFDESC_FATALTHRESHOLD);

	p_headerlessCopy = PLEX_assignDefaultBool(PLEX_DEFNAME_HEADERLESSCOPY, p_defHeaderlessCopy, PLEX_DEFDESC_HEADERLESSCOPY);

	p_memoryProfile = PLEX_assignDefaultUInt8(PLEX_DEFNAME_MEMORYPROFILE, 0, 3, p_defMemoryProfile, PLEX_DEFDESC_MEMORYPROFILE);

	p_memReport = PLEX_assignDefaultBool(PLEX_DEFNAME_MEMORYREPORT, p_defMemoryReport, PLEX_DEFDESC_MEMORYREPORT);

	p_memReportToFile = PLEX_assignDefaultBool(PLEX_DEFNAME_MEMORYREPORTTOFILE, p_defMemoryReportToFile, PLEX_DEFDESC_MEMORYREPORTTOFILE);

	if(p_width == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEWIDTH);
	if(p_height == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEHEIGHT);
	if(p_killOnEscape == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEKILLONESCAPE);
	if(p_killOnClose == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEKILLONCLOSE);
	if(p_allowResize == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEALLOWRESIZE);
	if(p_allowMaximize == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEALLOWMAXIMIZE);
	if(p_startMaximized == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPESTARTMAXIMIZE);
	if(p_disableSound == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEDISABLESOUND);
	if(p_cursorR == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPECURSORR);
	if(p_cursorG == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPECURSORG);
	if(p_cursorB == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPECURSORB);
	if(p_controllerPause == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPECONTROLLERPAUSE);
	if(p_disableController == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEDISABLECONTROLLER);
	if(p_disableJoystick == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEDISABLEJOYSTICK);
	if(p_disableKeyboard == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEDISABLEKEYBOARD);
	if(p_disableMouse == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPEDISABLEMOUSE);
	if(p_24hourTime == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TYPE24HRTIME);

	if(p_textureDimensLimit == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_TEXTUREDIMENSLIMIT);

	if(p_printErrors == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_PRINTERRORS);
	if(p_showErrors == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_SHOWERRORS);

	if(p_printErrorThreshold == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_PRINTERRORTHRESHOLD);
	if(p_showErrorThreshold == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_SHOWERRORTHRESHOLD);
	if(p_fatalErrorThreshold == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_FATALERRORTHRESHOLD);

	if(p_headerlessCopy == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_HEADERLESSCOPY);

	if(p_memoryProfile == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_MEMORYPROFILE);

	if(p_memReport == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_MEMORYREPORT);
	if(p_memReportToFile == -1) PLEX_error(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DEFAULTPOP, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULT_MEMORYREPORTTOFILE);
}

// reads the subject of a default string

static bool p_readSubject(PLEX_FAKESTRING_100* buffer, bool* read, FILE* config, const size_t errorline, const char* const errorfile)
{
	bool valid = false;

	int next = fgetc(config);

	PLEX_FAKESTRING_100 lBuffer = *buffer;

	while(next != '\r' && next != '\n')
	{
		if(next == '=')
		{
			valid = true;
			break;
		}else{
			if(next == EOF || next == '\0')
			{
				*read = false;
				break;
			}else lBuffer = PLEX_concatString100(lBuffer, next, 1);
		}

		next = fgetc(config);
	}

	lBuffer = PLEX_trimmedString100Int(lBuffer, " \t\r\n", errorline, errorfile);

	*buffer = lBuffer;

	return valid;
}

// read predicate of a default string

static void p_readPredicate(PLEX_FAKESTRING_100* buffer, PLEX_FAKESTRING_500* comment, bool* read, FILE* config, const size_t errorline, const char* const errorfile)
{
	int next = fgetc(config);

	PLEX_FAKESTRING_100 lBuffer = *buffer;
	PLEX_FAKESTRING_500 lComment = *comment;

	bool commented = false;

	while(next != '\r' && next != '\n')
	{
		if(next == EOF || next == '\0')
		{
			*read = false;
			break;
		}else{
			if(!commented && next == '#') commented = true;
			else
			{
				if(commented) lComment = PLEX_concatString500(lComment, next, 1);
				else lBuffer = PLEX_concatString100(lBuffer, next, 1);
			}
		}

		next = fgetc(config);
	}

	lBuffer = PLEX_trimmedString100Int(lBuffer, " \t\r\n", errorline, errorfile);
	lComment = PLEX_trimmedString500Int(lComment, " \t\r\n", errorline, errorfile);

	*buffer = lBuffer;
	*comment = lComment;
}

// checks if a subject is the name of a default

static bool p_checkDefault(const char* const subject, size_t len, P_DEFAULTENTRY* entry, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_100 subject2 = PLEX_createString100Int(subject, errorline, errorfile);

	return PLEX_compStrings100Int(subject2, entry->name, true, errorline, errorfile);
}

// adds a value to the string bank

static uint64_t p_addToStringBank(const char* const value, const size_t errorline, const char* const errorfile)
{
	if(PLEX_addStringToBankInt(value, p_stringBank, errorline, errorfile) == -1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONADDTOSTRINGBANK, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return -1;
	}

	PLEX_addStringToBankInt(value, p_stringBank, errorline, errorfile);

	return PLEX_stringBankCountInt(p_stringBank, errorline, errorfile) - 1;
}

// sets the default from the predicate

static void p_setDefault(const char* const predicate, size_t len, P_DEFAULTENTRY* entry, const bool ignoreRange, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_10 trueStr;
	PLEX_FAKESTRING_10 predicateStr;

	switch(entry->type)
	{
		case PLEX_DEF_UINT8:
		case PLEX_DEF_UINT32:
			entry->def = atoi(predicate);
		break;

		case PLEX_DEF_BOOL: // any value that isn't 'true' all lowercase will be considered false
			predicateStr = PLEX_createString10Int(predicate, errorline, errorfile);
			trueStr = PLEX_createString10Int(PLEX_DEFAULT_TRUE, errorline, errorfile);

			if(len == 4 && PLEX_compStrings10Int(predicateStr, trueStr, true, errorline, errorfile)) entry->def = 1;
			else entry->def = 0;
		break;

		case PLEX_DEF_DOUBLE:
			entry->def = strtod(predicate, NULL);
		break;

		case PLEX_DEF_STRING:
			entry->def = p_addToStringBank(predicate, errorline, errorfile);
		break;

		case PLEX_DEF_NONE: break;
	};

	if(!ignoreRange) entry->def = p_validateNumberDefault(entry->min, entry->max, entry->def);
}

// assumes the default's type and then sets it accordingly by subject and predicate

static void p_setDefaultGuessType(const char* const subject, const char* const predicate, const size_t predicateLen, P_DEFAULTENTRY* entry, const size_t errorline, const char* const errorfile)
{
	const PLEX_FAKESTRING_100 predicateStr = PLEX_createString100Int(predicate, errorline, errorfile);

	entry->name = PLEX_createString100Int(subject, errorline, errorfile);

	if(PLEX_isStringNumber100(predicateStr))
	{
		if(PLEX_isStringInteger100(predicateStr)) entry->type = PLEX_DEF_UINT32;
		else entry->type = PLEX_DEF_DOUBLE;
	}else{
		const PLEX_FAKESTRING_100 trueStr = PLEX_createString100Int(PLEX_DEFAULT_TRUE, errorline, errorfile);
		const PLEX_FAKESTRING_100 falseStr = PLEX_createString100Int(PLEX_DEFAULT_FALSE, errorline, errorfile);

		if(PLEX_compStrings100Int(predicateStr, trueStr, false, errorline, errorfile) || PLEX_compStrings100Int(predicateStr, falseStr, false, errorline, errorfile)) entry->type = PLEX_DEF_BOOL;
		else entry->type = PLEX_DEF_STRING;
	}

	p_setDefault(predicate, predicateLen, entry, true, errorline, errorfile);
}

// sets the comment on the entry

static void p_setComment(const char* const comment, P_DEFAULTENTRY* entry, const size_t errorline, const char* const errorfile)
{
	entry->comment = PLEX_createString500Int(comment, errorline, errorfile);
}

// saves the default as a string

static void p_saveDefault(const size_t index, FILE* config, const size_t errorline, const char* const errorfile)
{
	P_DEFAULTENTRY* entry = NULL;

	PLEX_FAKESTRING_100 sbuffer = PLEX_blankString100Int(errorline, errorfile);

	entry = (P_DEFAULTENTRY*)PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONSAVE, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return;
	}

	fwrite(PLEX_fts(entry->name), entry->name.len, 1, config);

	fwrite(" = ", 3, 1, config);

	switch(entry->type)
	{
		case PLEX_DEF_UINT8:
		case PLEX_DEF_UINT32:
			sbuffer = PLEX_createStringFromNumber100((unsigned)entry->def);
		break;

		case PLEX_DEF_BOOL:
			if(entry->def) sbuffer = PLEX_createString100Int(PLEX_DEFAULT_TRUE, errorline, errorfile);
			else sbuffer = PLEX_createString100Int(PLEX_DEFAULT_FALSE, errorline, errorfile);
		break;

		case PLEX_DEF_DOUBLE:
			sbuffer = PLEX_createStringFromNumber100(entry->def);
		break;

		case PLEX_DEF_STRING:
			sbuffer = PLEX_getDefaultStringInt(index, errorline, errorfile);
		break;

		case PLEX_DEF_NONE: break;
	};

	fwrite(PLEX_fts(sbuffer), sbuffer.len, 1, config);

	if(entry->comment.len)
	{
		fwrite(" # ", 3, 1, config);
		fwrite(PLEX_fts(entry->comment), entry->comment.len, 1, config);
	}

	fwrite(PLEX_NL, strlen(PLEX_NL), 1, config);
}

// returns the value at the index as a double

static double p_getDefaultValue(const size_t index, const size_t errorline, const char* const errorfile)
{
	P_DEFAULTENTRY* entry = NULL;

	if(index >= PLEX_expandArrayCountInt(p_entries, errorline, errorfile)) return 0;

	entry = (P_DEFAULTENTRY*)PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETVALUE, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return 0;
	}

	return entry->def;
}

// gets the default entry by it's name'

static int64_t p_getDefaultEntry(const char* const name, const size_t errorline, const char* const errorfile)
{
	const size_t entryCount = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

	const size_t nameLen = strlen(name);

	for(size_t ze = 0; ze < entryCount; ++ze)
	{
		P_DEFAULTENTRY* entry = (P_DEFAULTENTRY*)PLEX_getExpandArrayEntryInt(ze, p_entries, errorline, errorfile);

		if(entry == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETENTRY, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
			return 0;
		}

		if(p_checkDefault(name, nameLen, entry, errorline, errorfile)) return ze;
	}

	return -1;
}

static int64_t p_checkDefaultEntry(const char* const name, const double min, const double max, const size_t errorline, const char* const errorfile)
{
	const int64_t ret = p_getDefaultEntry(name, errorline, errorfile);

	if(ret != -1)
	{
		P_DEFAULTENTRY* entry = PLEX_getExpandArrayEntryInt(ret, p_entries, errorline, errorfile);

		if(entry == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONCHECKENTRY, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
			return -1;
		}

		entry->def = p_validateNumberDefault(min, max, entry->def);
	}

	return ret;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

bool PLEX_loadConfigInt(const char* fileloc, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_100 predicate = PLEX_blankString100Int(errorline, errorfile);
	PLEX_FAKESTRING_100 subject = PLEX_blankString100Int(errorline, errorfile);
	PLEX_FAKESTRING_500 comment = PLEX_blankString500Int(errorline, errorfile);

	bool read = true;

	FILE* config = NULL;

	if(fileloc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return false;
	}

	config = fopen(fileloc, "r");

	if(p_entries != NULL) PLEX_destroyExpandArrayInt(&p_entries, errorline, errorfile);
	p_entries = PLEX_genExpandArrayInt(PLEX_getMemProfileDefaultPreload(), sizeof(P_DEFAULTENTRY), errorline, errorfile);

	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return false;
	}

	if(p_stringBank != NULL) PLEX_destroyStringBankInt(&p_stringBank, errorline, errorfile);
	p_stringBank = PLEX_genStringBankInt(errorline, errorfile);

	if(p_stringBank == NULL)
	{
		// the genStringBankInt function should already toss a fatal error if generation fails
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_ERRORMESS_DEFAULT_STRINGBANK, errorline, errorfile);
		return false;
	}

	p_populateDefaults(errorline, errorfile);

	if(config == NULL)
	{
		const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_DEFAULTS_CONFIG);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_fts(targMessage), errorline, errorfile);
		return false;
	}

	while(read)
	{
		if(p_readSubject(&subject, &read, config, errorline, errorfile))
		{
			bool assigned = false;

			if(!subject.len) continue;

			p_readPredicate(&predicate, &comment, &read, config, errorline, errorfile);

			if(!predicate.len) continue;

			for(size_t ze = 0; ze < p_entries->count; ++ze)
			{
				P_DEFAULTENTRY* entry = (P_DEFAULTENTRY*)PLEX_getExpandArrayEntry(ze, p_entries);

				if(entry == NULL)
				{
					PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
					return false;
				}

				if(p_checkDefault((char*)&subject, subject.len, entry, errorline, errorfile))
				{
					p_setDefault((const char*)&predicate, predicate.len, entry, false, errorline, errorfile);
					p_setComment((const char*)&comment, entry, errorline, errorfile);
					assigned = true;
				}
			}

			if(!assigned)
			{
				P_DEFAULTENTRY* entry = NULL;

				if(!PLEX_incrementExpandArray(p_entries))
				{
					PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
					return false;
				}

				entry = PLEX_getExpandArrayLast(p_entries);

				if(entry == NULL)
				{
					PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONLOADCONFIG, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
					return false;
				}

				p_setDefaultGuessType(PLEX_fts(subject), PLEX_fts(predicate), predicate.len, entry, errorline, errorfile);
				p_setComment(PLEX_fts(comment), entry, errorline, errorfile);
			}
		}

		predicate = PLEX_blankString100Int(errorline, errorfile);
		subject = PLEX_blankString100Int(errorline, errorfile);
		comment = PLEX_blankString500Int(errorline, errorfile);
	}

	fclose(config);

	return true;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startDefaultsInt(const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	if(!PLEX_loadConfigInt(PLEX_DEFAULT_CONFIGPATH, errorline, errorfile))
	{
		p_stringBank = PLEX_genStringBankInt(errorline, errorfile); // keep here, if the load config succeeds the string bank is allocated

		if(p_stringBank == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONSTART, PLEX_ERRORMESS_DEFAULT_STRINGBANK, errorline, errorfile);
			return false;
		}

		p_populateDefaults(errorline, errorfile); // keep here, if the load config succeeds it populates defaults anyway
		// don't return here
	}

	// these must be set here because 'error subsystem' is initialized before 'default subsystem'

	PLEX_printErrors(PLEX_DEF_printErrors());
	PLEX_showErrors(PLEX_DEF_showErrors());
	PLEX_dumpErrors(PLEX_DEF_dumpErrors());

	PLEX_setErrorPrintingThreshold((PLEX_ERROR_SEVERITY)PLEX_DEF_printErrorThreshold());
	PLEX_setErrorShowingThreshold((PLEX_ERROR_SEVERITY)PLEX_DEF_showErrorThreshold());
	PLEX_setErrorFatalThreshold((PLEX_ERROR_SEVERITY)PLEX_DEF_fatalErrorThreshold());

	// these must be set here because 'memory subsystem' is initialized before 'default subsystem'

	if(!PLEX_DEF_memoryReport()) PLEX_unflagMemReport();
	if(!PLEX_DEF_memoryReportToFile() || !PLEX_DEF_memoryReport()) PLEX_unflagMemReportToFileInt(errorline, errorfile);

	PLEX_setMemProfile(PLEX_DEF_memProfile());

	PLEX_updateMemProfile();

	if(p_entries != NULL) PLEX_setGrowthUnitProtoExpandArrayInt(PLEX_getMemProfileDefaultPreload(), p_entries, errorline, errorfile);

	p_running = true;

	return true;
}

void PLEX_endDefaultsInt(const size_t errorline, const char* const errorfile)
{
	FILE* config = NULL;

	size_t count = 0;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return;
	}

	config = fopen(PLEX_DEFAULT_CONFIGPATH, "w+");

	if(config == NULL)
	{
		const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(PLEX_DEFAULT_CONFIGPATH, PLEX_ERRORMESS_DEFAULTS_CONFIG);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONEND, PLEX_fts(targMessage), errorline, errorfile);
	}else{
		count = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

		for(size_t ze = 0; ze < count; ++ze) p_saveDefault(ze, config, errorline, errorfile);

		fclose(config);
	}

	PLEX_destroyExpandArrayInt(&p_entries, errorline, errorfile);
	PLEX_destroyStringBankInt(&p_stringBank, errorline, errorfile);

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

// the maximum a texture dimension can be

int64_t PLEX_assignDefaultUInt8Int(const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	double adef = 0;

	// do not check p_running here //

	if(p_entries == NULL)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNUINT8, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONASSIGNUINT8, PLEX_ERRORMESS_DEFAULT_NONAME, errorline, errorfile);
		return -1;
	}

	adef = p_validateNumberDefault(min, max, def);

	return p_assignDefault(name, PLEX_DEF_UINT8, min, max, adef, comment, errorline, errorfile);
}

int64_t PLEX_assignDefaultUInt32Int(const char* const name, const uint32_t min, const uint32_t max, const uint32_t def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	double adef = 0;

	// do not check p_running here //

	if(p_entries == NULL)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNUINT32, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONASSIGNUINT32, PLEX_ERRORMESS_DEFAULT_NONAME, errorline, errorfile);
		return -1;
	}

	adef = p_validateNumberDefault(min, max, def);

	return p_assignDefault(name, PLEX_DEF_UINT32, min, max, adef, comment, errorline, errorfile);
}

int64_t PLEX_assignDefaultBoolInt(const char* const name, const bool def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	// do not check p_running here //

	if(p_entries == NULL)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNBOOL, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONASSIGNBOOL, PLEX_ERRORMESS_DEFAULT_NONAME, errorline, errorfile);
		return -1;
	}

	return p_assignDefault(name, PLEX_DEF_BOOL, false, true, def, comment, errorline, errorfile);
}

int64_t PLEX_assignDefaultDoubleInt(const char* const name, const double min, const double max, const double def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	double adef = 0;

	// do not check p_running here //

	if(p_entries == NULL)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNDOUBLE, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNDOUBLE, PLEX_ERRORMESS_DEFAULT_NONAME, errorline, errorfile);
		return -1;
	}

	adef = p_validateNumberDefault(min, max, def);

	return p_assignDefault(name, PLEX_DEF_DOUBLE, false, true, adef, comment, errorline, errorfile);
}

int64_t PLEX_assignDefaultStringInt(const char* const name, const char* const value, const char* const comment, const size_t errorline, const char* const errorfile)
{
	int64_t adef = 0;

	// do not check p_running here //

	if(p_entries == NULL)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNSTRING, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONASSIGNSTRING, PLEX_ERRORMESS_DEFAULT_NONAME, errorline, errorfile);
		return -1;
	}

	if(value == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONASSIGNSTRING, PLEX_ERRORMESS_GENERIC_VALUE, errorline, errorfile);
		return -1;
	}

	adef = p_addToStringBank(value, errorline, errorfile);

	if(adef == -1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONASSIGNSTRING, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return -1;
	}

	return p_assignDefault(name, PLEX_DEF_STRING, adef, adef + 1, adef, comment, errorline, errorfile);
}

int64_t PLEX_addCustomDefaultUInt8Int(const char* const name, const uint8_t min, const uint8_t max, const uint8_t def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	int64_t index = -1;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMUINT8, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMUINT8, PLEX_ERRORMESS_GENERIC_NAME, errorline, errorfile);
		return -1;
	}

	index = p_checkDefaultEntry(name, min, max, errorline, errorfile);

	if(index != -1) return index;

	return PLEX_assignDefaultUInt8Int(name, min, max, def, comment, errorline, errorfile);
}

int64_t PLEX_addCustomDefaultUInt32Int(const char* const name, const uint32_t min, const uint32_t max, const uint32_t def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	int64_t index = -1;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMUINT32, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMUINT32, PLEX_ERRORMESS_GENERIC_NAME, errorline, errorfile);
		return -1;
	}

	index = p_checkDefaultEntry(name, min, max, errorline, errorfile);

	if(index != -1) return index;

	return PLEX_assignDefaultUInt32Int(name, min, max, def, comment, errorline, errorfile);
}

int64_t PLEX_addCustomDefaultBoolInt(const char* const name, const bool def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	int64_t index = -1;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMBOOL, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMBOOL, PLEX_ERRORMESS_GENERIC_NAME, errorline, errorfile);
		return -1;
	}

	index = p_checkDefaultEntry(name, false, true, errorline, errorfile);

	if(index != -1) return index;

	return PLEX_assignDefaultBoolInt(name, def, comment, errorline, errorfile);
}

int64_t PLEX_addCustomDefaultDoubleInt(const char* const name, const double min, const double max, const double def, const char* const comment, const size_t errorline, const char* const errorfile)
{
	int64_t index = -1;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMDOUBLE, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMDOUBLE, PLEX_ERRORMESS_GENERIC_NAME, errorline, errorfile);
		return -1;
	}

	index = p_checkDefaultEntry(name, min, max, errorline, errorfile);

	if(index != -1) return index;

	return PLEX_assignDefaultDoubleInt(name, min, max, def, comment, errorline, errorfile);
}

int64_t PLEX_addCustomDefaultStringInt(const char* const name, const char* const value, const char* const comment, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	int64_t index = -1;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMSTRING, errorline, errorfile);
		return -1;
	}

	if(name == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMSTRING, PLEX_ERRORMESS_GENERIC_NAME, errorline, errorfile);
		return -1;
	}

	if(value == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMSTRING, PLEX_ERRORMESS_GENERIC_VALUE, errorline, errorfile);
		return -1;
	}

	if(p_stringBank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMSTRING, PLEX_ERRORMESS_DEFAULT_STRINGBANK, errorline, errorfile);
		return -1;
	}

	count = PLEX_stringBankCountInt(p_stringBank, errorline, errorfile);

	if(!count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONADDCUSTOMSTRING, PLEX_ERRORMESS_GENERIC_COUNT, errorline, errorfile);
		return -1;
	}

	index = p_checkDefaultEntry(name, 0, count - 1, errorline, errorfile);

	if(index != -1) return index;

	return PLEX_assignDefaultStringInt(name, value, comment, errorline, errorfile);
}

// getters ------------------------------------------------------------------------------------------------------------------

uint32_t PLEX_DEF_widthInt(const size_t errorline, const char* const errorfile)
{
	if(p_width == -1) return p_defWidth;

	return PLEX_getDefaultUint32Int(p_width, errorline, errorfile);
}

uint32_t PLEX_DEF_heightInt(const size_t errorline, const char* const errorfile)
{
	if(p_height == -1) return p_defHeight;

	return PLEX_getDefaultUint32Int(p_height, errorline, errorfile);
}

bool PLEX_DEF_killOnEscapeInt(const size_t errorline, const char* const errorfile)
{
	if(p_killOnEscape == -1) return p_defKillOnClose;

	return PLEX_getDefaultBoolInt(p_killOnEscape, errorline, errorfile);
}

bool PLEX_DEF_killOnCloseInt(const size_t errorline, const char* const errorfile)
{
	if(p_killOnClose == -1) return p_defKillOnClose;

	return PLEX_getDefaultBoolInt(p_killOnClose, errorline, errorfile);
}

bool PLEX_DEF_allowResizeInt(const size_t errorline, const char* const errorfile)
{
	if(p_allowResize == -1) return p_defAllowResize;

	return PLEX_getDefaultBoolInt(p_allowResize, errorline, errorfile);
}

bool PLEX_DEF_allowMaximizeInt(const size_t errorline, const char* const errorfile)
{
	if(p_allowMaximize == -1) return p_defAllowMaximize;

	return PLEX_getDefaultBoolInt(p_allowMaximize, errorline, errorfile);
}

bool PLEX_DEF_startMaximizedInt(const size_t errorline, const char* const errorfile)
{
	if(p_startMaximized == -1) return p_defStartMaximize;

	return PLEX_getDefaultBoolInt(p_startMaximized, errorline, errorfile);
}

bool PLEX_DEF_disableAudioInt(const size_t errorline, const char* const errorfile)
{
	if(p_disableSound == -1) return p_defDisableSound;

	return PLEX_getDefaultBoolInt(p_disableSound, errorline, errorfile);
}

uint8_t PLEX_DEF_cursorRInt(const size_t errorline, const char* const errorfile)
{
	if(p_cursorR == -1) return p_defCursorR;

	return PLEX_getDefaultUint8Int(p_cursorR, errorline, errorfile);
}

uint8_t PLEX_DEF_cursorGInt(const size_t errorline, const char* const errorfile)
{
	if(p_cursorG == -1) return p_defCursorG;

	return PLEX_getDefaultUint8Int(p_cursorG, errorline, errorfile);
}

uint8_t PLEX_DEF_cursorBInt(const size_t errorline, const char* const errorfile)
{
	if(p_cursorB == -1) return p_defCursorB;

	return PLEX_getDefaultUint8Int(p_cursorB, errorline, errorfile);
}

double PLEX_DEF_cursorWInt(const size_t errorline, const char* const errorfile)
{
	if(p_cursorW == -1) return p_defCursorW;

	return PLEX_getDefaultDoubleInt(p_cursorW, errorline, errorfile);
}

double PLEX_DEF_cursorHInt(const size_t errorline, const char* const errorfile)
{
	if(p_cursorH == -1) return p_defCursorH;

	return PLEX_getDefaultDoubleInt(p_cursorH, errorline, errorfile);
}

bool PLEX_DEF_controllerPauseInt(const size_t errorline, const char* const errorfile)
{
	if(p_controllerPause == -1) return p_defControllerPause;

	return PLEX_getDefaultBoolInt(p_controllerPause, errorline, errorfile);
}

bool PLEX_DEF_disableControllerInt(const size_t errorline, const char* const errorfile)
{
	if(p_disableController == -1) return p_defDisableController;

	return PLEX_getDefaultBoolInt(p_disableController, errorline, errorfile);
}

bool PLEX_DEF_disableJoystickInt(const size_t errorline, const char* const errorfile)
{
	if(p_disableJoystick == -1) return p_defDisableJoystick;

	return PLEX_getDefaultBoolInt(p_disableJoystick, errorline, errorfile);
}

bool PLEX_DEF_disableKeyboardInt(const size_t errorline, const char* const errorfile)
{
	if(p_disableKeyboard == -1) return p_defDisableKeyboard;

	return PLEX_getDefaultBoolInt(p_disableController, errorline, errorfile);
}

bool PLEX_DEF_disableMouseInt(const size_t errorline, const char* const errorfile)
{
	if(p_disableMouse == -1) return p_defDisableMouse;

	return PLEX_getDefaultBoolInt(p_disableMouse, errorline, errorfile);
}

bool PLEX_DEF_24HourTimeInt(const size_t errorline, const char* const errorfile)
{
	if(p_24hourTime == -1) return p_def42Hour;

	return PLEX_getDefaultBoolInt(p_24hourTime, errorline, errorfile);
}

uint32_t PLEX_DEF_textureDimensLimitInt(const size_t errorline, const char* const errorfile)
{
	if(p_textureDimensLimit == -1) return p_defTextureDimensLimit;

	return PLEX_getDefaultUint32Int(p_textureDimensLimit, errorline, errorfile);
}

bool PLEX_DEF_printErrorsInt(const size_t errorline, const char* const errorfile)
{
	if(p_printErrors == -1) return p_defShowErrors;

	return PLEX_getDefaultBoolInt(p_printErrors, errorline, errorfile);
}

bool PLEX_DEF_showErrorsInt(const size_t errorline, const char* const errorfile)
{
	if(p_showErrors == -1) return p_defShowErrors;

	return PLEX_getDefaultBoolInt(p_showErrors, errorline, errorfile);
}

bool PLEX_DEF_dumpErrorsInt(const size_t errorline, const char* const errorfile)
{
	if(p_dumpErrors == -1) return p_defDumpErrors;

	return PLEX_getDefaultBoolInt(p_dumpErrors, errorline, errorfile);
}

uint8_t PLEX_DEF_printErrorThresholdInt(const size_t errorline, const char* const errorfile)
{
	if(p_printErrorThreshold == -1) return p_defPrintErrorThreshhold;

	return PLEX_getDefaultUint8Int(p_printErrorThreshold, errorline, errorfile);
}

uint8_t PLEX_DEF_showErrorThresholdInt(const size_t errorline, const char* const errorfile)
{
	if(p_showErrorThreshold == -1) return p_defShowErrorThreshold;

	return PLEX_getDefaultUint8Int(p_showErrorThreshold, errorline, errorfile);
}

uint8_t PLEX_DEF_fatalErrorThresholdInt(const size_t errorline, const char* const errorfile)
{
	if(p_fatalErrorThreshold == -1) return p_defFatalErrorThreshold;

	return PLEX_getDefaultUint8Int(p_fatalErrorThreshold, errorline, errorfile);
}

bool PLEX_DEF_headerlessCopyInt(const size_t errorline, const char* const errorfile)
{
	if(p_headerlessCopy == -1) return p_defHeaderlessCopy;

	return PLEX_getDefaultBoolInt(p_headerlessCopy, errorline, errorfile);
}

uint8_t PLEX_DEF_memProfileInt(const size_t errorline, const char* const errorfile)
{
	if(p_memoryProfile == -1) return p_defMemoryProfile;

	return PLEX_getDefaultUint8Int(p_memoryProfile, errorline, errorfile);
}

bool PLEX_DEF_memoryReportInt(const size_t errorline, const char* const errorfile)
{
	if(p_memReport == -1) return p_defMemoryReport;

	return PLEX_getDefaultBoolInt(p_memReport, errorline, errorfile);
}

bool PLEX_DEF_memoryReportToFileInt(const size_t errorline, const char* const errorfile)
{
	if(p_memReportToFile == -1) return p_defMemoryReportToFile;

	return PLEX_getDefaultBoolInt(p_memReportToFile, errorline, errorfile);
}

// do not use getDefault for these!

uint32_t PLEX_DEF_minWindowW(){ return p_minWidth; }
uint32_t PLEX_DEF_minWindowH(){ return p_minHeight; }

uint32_t PLEX_DEF_maxWindowW(){ return p_maxWidth; }
uint32_t PLEX_DEF_maxWindowH(){ return p_maxHeight; }

PLEX_FAKESTRING_100 PLEX_getDefaultNameInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t entryCount = 0;

	P_DEFAULTENTRY* entry = NULL;

	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETNAME, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	entryCount = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

	if(index >= entryCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONGETNAME, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	entry = PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETNAME, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	return entry->name;
}

PLEX_DEF_ENTRYTYPE PLEX_getDefaultTypeInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t entryCount = 0;

	P_DEFAULTENTRY* entry = NULL;

	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETYPE, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_DEF_NONE;
	}

	entryCount = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

	if(index >= entryCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONGETYPE, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return PLEX_DEF_NONE;
	}

	entry = PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETYPE, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_DEF_NONE;
	}

	return entry->type;
}

PLEX_FAKESTRING_500 PLEX_getDefaultCommentInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t entryCount = 0;

	P_DEFAULTENTRY* entry = NULL;

	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETCOMMENT, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_blankString500Int(errorline, errorfile);
	}

	entryCount = PLEX_expandArrayCount(p_entries);

	if(index >= entryCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONGETCOMMENT, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return PLEX_blankString500Int(errorline, errorfile);
	}

	entry = PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETCOMMENT, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_blankString500Int(errorline, errorfile);
	}

	return entry->comment;
}

double PLEX_getDefaultMinimumInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t entryCount = 0;

	P_DEFAULTENTRY* entry = NULL;

	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETMINIMUM, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return 0;
	}

	entryCount = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

	if(index >= entryCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONGETMINIMUM, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return 0;
	}

	entry = PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETMINIMUM, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return 0;
	}

	return entry->min;
}

double PLEX_getDefaultMaximumInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t entryCount = 0;

	P_DEFAULTENTRY* entry = NULL;

	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETMAXIMUM, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return 0;
	}

	entryCount = PLEX_expandArrayCountInt(p_entries, errorline, errorfile);

	if(index >= entryCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONGETMAXIMUM, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return 0;
	}

	entry = PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETMAXIMUM, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return 0;
	}

	return entry->max;
}

uint8_t PLEX_getDefaultUint8Int(const size_t index, const size_t errorline, const char* const errorfile)
{
	return (uint8_t)p_getDefaultValue(index, errorline, errorfile);
}

uint32_t PLEX_getDefaultUint32Int(const size_t index, const size_t errorline, const char* const errorfile)
{
	return (uint32_t)p_getDefaultValue(index, errorline, errorfile);
}

bool PLEX_getDefaultBoolInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	return p_getDefaultValue(index, errorline, errorfile);
}

double PLEX_getDefaultDoubleInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	return p_getDefaultValue(index, errorline, errorfile);
}

PLEX_FAKESTRING_100 PLEX_getDefaultStringInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_500 ret;

	P_DEFAULTENTRY* entry = NULL;

	if(p_stringBank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DEFAULTS_ONGETSTRING, PLEX_ERRORMESS_DEFAULT_STRINGBANK, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	if(index >= PLEX_expandArrayCountInt(p_entries, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DEFAULTS_ONGETSTRING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	entry = (P_DEFAULTENTRY*)PLEX_getExpandArrayEntryInt(index, p_entries, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DEFAULTS_ONGETSTRING, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	ret = PLEX_getStringBankEntry(entry->def, p_stringBank);

	if(!ret.len)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETSTRING, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	return PLEX_createString100Int(PLEX_fts(ret), errorline, errorfile);
}

uint8_t PLEX_getDefaultUint8ByNameInt(const char* const name, const size_t errorline, const char* const errorfile)
{
	const uint64_t index = p_getDefaultEntry(name, errorline, errorfile);

	if(index == -1) return 0;

	return PLEX_getDefaultUint8Int(index, errorline, errorfile);
}

uint32_t PLEX_getDefaultUint32ByNameInt(const char* const name, const size_t errorline, const char* const errorfile)
{
	const uint64_t index = p_getDefaultEntry(name, errorline, errorfile);

	if(index == -1) return 0;

	return PLEX_getDefaultUint32Int(index, errorline, errorfile);
}

bool PLEX_getDefaultBoolByNameInt(const char* const name, const size_t errorline, const char* const errorfile)
{
	const uint64_t index = p_getDefaultEntry(name, errorline, errorfile);

	if(index == -1) return false;

	return PLEX_getDefaultBoolInt(index, errorline, errorfile);
}

double PLEX_getDefaultDoubleByNameInt(const char* const name, const size_t errorline, const char* const errorfile)
{
	const uint64_t index = p_getDefaultEntry(name, errorline, errorfile);

	if(index == -1) return 0;

	return PLEX_getDefaultDoubleInt(index, errorline, errorfile);
}

PLEX_FAKESTRING_100 PLEX_getDefaultStringByNameInt(const char* const name, const size_t errorline, const char* const errorfile)
{
	const uint64_t index = p_getDefaultEntry(name, errorline, errorfile);

	if(index == -1) return PLEX_blankString100Int(errorline, errorfile);

	return PLEX_getDefaultStringInt(index, errorline, errorfile);
}

size_t PLEX_defaultCountInt(const size_t errorline, const char* const errorfile)
{
	if(p_entries == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DEFAULT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DEFAULTS_ONGETCOUNT, PLEX_ERRORMESS_DEFAULT_ENTRIES, errorline, errorfile);
		return 0;
	}

	return PLEX_expandArrayCountInt(p_entries, errorline, errorfile);
}
