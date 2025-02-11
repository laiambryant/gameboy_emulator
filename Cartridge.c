#include "Cartridge.h"

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

static const char* LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

cartridge_context* init_cart(char* cartridge_path) {
	cartridge_context* ctx = malloc(sizeof(cartridge_context));
	if (ctx == NULL) {
		printf("Failed to allocate memory for cartridge context\n");
		return NULL;
	}
    cart_load(ctx, cartridge_path);
	return ctx;
}

int destroy_cart(cartridge_context* ctx) {
	free(ctx->rom_data);
	free(ctx);
	return 0;
}

const char* cart_lic_name(cartridge_context* ctx) {
    if (ctx->header->new_lic_code <= LIC_CODE_SIZE) {
        return LIC_CODE[ctx->header->lic_code];
    }
    return "UNKNOWN";
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
        return 1;
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
        return 1;
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
        return 1;
    }
    fread(ctx->rom_data, ctx->rom_size, 1, fd);
    fclose(fd);  
	return 0;
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