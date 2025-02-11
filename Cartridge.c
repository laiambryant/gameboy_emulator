#ifndef CARTRIDGE
#define	CARTRIDGE
#include "Cartridge.h"
#endif 

static const u8 LIC_CODE_SIZE = 0xA4;
static const u8 CART_TYPE_SIZE = 0x22;
static const u16 ROM_HEADER_END = 0x100;
static const u16 CHECKSUM_START = 0x0134;
static const u16 CHECKSUM_END = 0x014C;

static const char* ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char* LIC_CODE[] = {
    [0x00] = "None",
    [0x01] = "Nintendo",
    [0x08] = "Capcom",
    [0x09] = "HOT-B",
    [0x0A] = "Jaleco",
    [0x0B] = "Coconuts Japan",
    [0x0C] = "Elite Systems",
    [0x13] = "EA (Electronic Arts)",
    [0x18] = "Hudson Soft",
    [0x19] = "ITC Entertainment",
    [0x1A] = "Yanoman",
    [0x1D] = "Japan Clary",
    [0x1F] = "Virgin Games Ltd.3",
    [0x24] = "PCM Complete",
    [0x25] = "San-X",
    [0x28] = "Kemco",
    [0x29] = "SETA Corporation",
    [0x30] = "Infogrames5",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Not Old Licensee",
    [0x34] = "Konami",
    [0x35] = "HectorSoft",
    [0x38] = "Capcom",
    [0x39] = "Banpresto",
    [0x3C] = "Entertainment Interactive (stub)",
    [0x3E] = "Gremlin",
    [0x41] = "Ubi Soft1",
    [0x42] = "Atlus",
    [0x44] = "Malibu Interactive",
    [0x46] = "Angel",
    [0x47] = "Spectrum HoloByte",
    [0x49] = "Irem",
    [0x4A] = "Virgin Games Ltd.3",
    [0x4D] = "Malibu Interactive",
    [0x4F] = "U.S. Gold",
    [0x50] = "Absolute",
    [0x51] = "Acclaim Entertainment",
    [0x52] = "Activision",
    [0x53] = "Sammy USA Corporation",
    [0x54] = "GameTek",
    [0x55] = "Park Place13",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x59] = "Milton Bradley Company",
    [0x5A] = "Mindscape",
    [0x5B] = "Romstar",
    [0x5C] = "Naxat Soft14",
    [0x5D] = "Tradewest",
    [0x60] = "Titus Interactive",
    [0x61] = "Virgin Games Ltd.3",
    [0x67] = "Ocean Software",
    [0x69] = "EA (Electronic Arts)",
    [0x6E] = "Elite Systems",
    [0x6F] = "Electro Brain",
    [0x70] = "Infogrames5",
    [0x71] = "Interplay Entertainment",
    [0x72] = "Broderbund",
    [0x73] = "Sculptured Software6",
    [0x75] = "The Sales Curve Limited7",
    [0x78] = "THQ",
    [0x79] = "Accolade15",
    [0x7A] = "Triffix Entertainment",
    [0x7C] = "MicroProse",
    [0x7F] = "Kemco",
    [0x80] = "Misawa Entertainment",
    [0x83] = "LOZC G.",
    [0x86] = "Tokuma Shoten",
    [0x8B] = "Bullet-Proof Software2",
    [0x8C] = "Vic Tokai Corp.16",
    [0x8E] = "Ape Inc.17",
    [0x8F] = "I’Max18",
    [0x91] = "Chunsoft Co.8",
    [0x92] = "Video System",
    [0x93] = "Tsubaraya Productions",
    [0x95] = "Varie",
    [0x96] = "Yonezawa19/S’Pal",
    [0x97] = "Kemco",
    [0x99] = "Arc",
    [0x9A] = "Nihon Bussan",
    [0x9B] = "Tecmo",
    [0x9C] = "Imagineer",
    [0x9D] = "Banpresto",
    [0x9F] = "Nova",
    [0xA1] = "Hori Electric",
    [0xA2] = "Bandai",
    [0xA4] = "Konami",
    [0xA6] = "Kawada",
    [0xA7] = "Takara",
    [0xA9] = "Technos Japan",
    [0xAA] = "Broderbund",
    [0xAC] = "Toei Animation",
    [0xAD] = "Toho",
    [0xAF] = "Namco",
    [0xB0] = "Acclaim Entertainment",
    [0xB1] = "ASCII Corporation or Nexsoft",
    [0xB2] = "Bandai",
    [0xB4] = "Square Enix",
    [0xB6] = "HAL Laboratory",
    [0xB7] = "SNK",
    [0xB9] = "Pony Canyon",
    [0xBA] = "Culture Brain",
    [0xBB] = "Sunsoft",
    [0xBD] = "Sony Imagesoft",
    [0xBF] = "Sammy Corporation",
    [0xC0] = "Taito",
    [0xC2] = "Kemco",
    [0xC3] = "Square",
    [0xC4] = "Tokuma Shoten",
    [0xC5] = "Data East",
    [0xC6] = "Tonkin House",
    [0xC8] = "Koei",
    [0xC9] = "UFL",
    [0xCA] = "Ultra Games",
    [0xCB] = "VAP, Inc.",
    [0xCC] = "Use Corporation",
    [0xCD] = "Meldac",
    [0xCE] = "Pony Canyon",
    [0xCF] = "Angel",
    [0xD0] = "Taito",
    [0xD1] = "SOFEL (Software Engineering Lab)",
    [0xD2] = "Quest",
    [0xD3] = "Sigma Enterprises",
    [0xD4] = "ASK Kodansha Co.",
    [0xD6] = "Naxat Soft14",
    [0xD7] = "Copya System",
    [0xD9] = "Banpresto",
    [0xDA] = "Tomy",
    [0xDB] = "LJN",
    [0xDD] = "Nippon Computer Systems",
    [0xDE] = "Human Ent.",
    [0xDF] = "Altron",
    [0xE0] = "Jaleco",
    [0xE1] = "Towa Chiki",
    [0xE2] = "Yutaka # Needs more info",
    [0xE3] = "Varie",
    [0xE5] = "Epoch",
    [0xE7] = "Athena",
    [0xE8] = "Asmik Ace Entertainment",
    [0xE9] = "Natsume",
    [0xEA] = "King Records",
    [0xEB] = "Atlus",
    [0xEC] = "Epic/Sony Records",
    [0xEE] = "IGS",
    [0xF0] = "A Wave",
    [0xF3] = "Extreme Entertainment",
    [0xFF] = "LJN"
};

static const char* NEW_LIC_CODE[] = {
    [0x00] = "None",
[0x01] = "Nintendo Research & Development 1",
[0x08] = "Capcom",
[0x13] = "EA (Electronic Arts)",
[0x18] = "Hudson Soft",
[0x19] = "B-AI",
[0x20] = "KSS",
[0x22] = "Planning Office WADA",
[0x24] = "PCM Complete",
[0x25] = "San-X",
[0x28] = "Kemco",
[0x29] = "SETA Corporation",
[0x30] = "Viacom",
[0x31] = "Nintendo",
[0x32] = "Bandai",
[0x33] = "Ocean Software/Acclaim Entertainment",
[0x34] = "Konami",
[0x35] = "HectorSoft",
[0x37] = "Taito",
[0x38] = "Hudson Soft",
[0x39] = "Banpresto",
[0x41] = "Ubi Soft1",
[0x42] = "Atlus",
[0x44] = "Malibu Interactive",
[0x46] = "Angel",
[0x47] = "Bullet-Proof Software2",
[0x49] = "Irem",
[0x50] = "Absolute",
[0x51] = "Acclaim Entertainment",
[0x52] = "Activision",
[0x53] = "Sammy USA Corporation",
[0x54] = "Konami",
[0x55] = "Hi Tech Expressions",
[0x56] = "LJN",
[0x57] = "Matchbox",
[0x58] = "Mattel",
[0x59] = "Milton Bradley Company",
[0x60] = "Titus Interactive",
[0x61] = "Virgin Games Ltd.3",
[0x64] = "Lucasfilm Games4",
[0x67] = "Ocean Software",
[0x69] = "EA (Electronic Arts)",
[0x70] = "Infogrames5",
[0x71] = "Interplay Entertainment",
[0x72] = "Broderbund",
[0x73] = "Sculptured Software6",
[0x75] = "The Sales Curve Limited7",
[0x78] = "THQ",
[0x79] = "Accolade",
[0x80] = "Misawa Entertainment",
[0x83] = "lozc",
[0x86] = "Tokuma Shoten",
[0x87] = "Tsukuda Original",
[0x91] = "Chunsoft Co.8",
[0x92] = "Video System",
[0x93] = "Ocean Software/Acclaim Entertainment",
[0x95] = "Varie",
[0x96] = "Yonezawa/s’pal",
[0x97] = "Kaneko",
[0x99] = "Pack-In-Video",
[0x9A] = "Bottom Up",
[0xA4] = "Konami (Yu-Gi-Oh!)",
[0xBL] = "MTO",
[0xDA] = "Kodansha"
};

static cartridge_context ctx = { 0 };

cartridge_context* init_cart(char* cartridge_path) {
	cart_load(&ctx, cartridge_path);
	return &ctx;
}

void destroy_cart(cartridge_context* ctx) {
	return;
}

const char* cart_lic_name(cartridge_context* ctx) {
    return LIC_CODE[ctx->header->lic_code];
}

const char* cart_type_name(cartridge_context* ctx) {
    if (ctx->header->type <= CART_TYPE_SIZE) {
        return ROM_TYPES[ctx->header->type];
    }
    return "UNKNOWN";
}

int cart_load(cartridge_context* ctx, char* cart) {
    snprintf(ctx->filename, sizeof(ctx->filename), "%s", cart);
	if (!read_rom(ctx,cart)) 
        return 0;
    ctx->header = (rom_header*)(ctx->rom_data + ROM_HEADER_END);
    ctx->header->title[15] = 0;
	print_debug(ctx);
    u16 x = 0;
    for (u16 i = CHECKSUM_START; i <= CHECKSUM_END; i++) {
        x = x - ctx->rom_data[i] - 1;
    }
    printf("\t Checksum : %2.2X (%s)\n", ctx->header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");
    return 0;
}

int read_rom(cartridge_context* ctx, char* cart) {
    FILE* fd = fopen(cart, "r");
    if (!fd) {
        printf("Failed to open: %s\n", cart);
        return 0;
    }
    printf("Opened: %s\n", ctx->filename);
    fseek(fd, 0, SEEK_END);
    ctx->rom_size = ftell(fd);
    printf("Rom Size: %d bytes\n", ctx->rom_size);
    rewind(fd);
    ctx->rom_data = malloc(ctx->rom_size);
    printf("Allocated: %d bytes\n", ctx->rom_size);
    if (ctx->rom_data == NULL) {
        printf("Failed to allocate memory for ROM\n");
        fclose(fd);
        return 0;
    }
    fread(ctx->rom_data, ctx->rom_size, 1, fd);
    fclose(fd);  
	return 1;
}

void print_debug(cartridge_context* ctx) {
    printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", ctx->header->title);
    printf("\t Type     : %2.2X (%s)\n", ctx->header->type, cart_type_name(ctx));
    printf("\t ROM Size : %d KB\n", 32 << ctx->header->rom_size);
    printf("\t RAM Size : %2.2X\n", ctx->header->ram_size);
    printf("\t LIC Code : %2.2X (%s)\n", ctx->header->lic_code, cart_lic_name(ctx));
    printf("\t ROM Vers : %2.2X\n", ctx->header->version);
}
void cart_write(u16 address, u8 data) {
    ctx.rom_data[address] = data;
}

u8 cart_read( u16 address) {
    return ctx.rom_data[address];
}