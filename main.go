package main

import (
	"log"
	"os"

	"github.com/hajimehoshi/ebiten/v2"

	"gameboy_emulator/internal/emulator"
)

const (
	scale = 4
)

type Game struct {
	emu *emulator.Emulator
	img *ebiten.Image
}

func (g *Game) Update() error {
	input := emulator.InputState{
		A:      ebiten.IsKeyPressed(ebiten.KeyZ),
		B:      ebiten.IsKeyPressed(ebiten.KeyX),
		Start:  ebiten.IsKeyPressed(ebiten.KeyEnter),
		Select: ebiten.IsKeyPressed(ebiten.KeyTab),
		Up:     ebiten.IsKeyPressed(ebiten.KeyArrowUp),
		Down:   ebiten.IsKeyPressed(ebiten.KeyArrowDown),
		Left:   ebiten.IsKeyPressed(ebiten.KeyArrowLeft),
		Right:  ebiten.IsKeyPressed(ebiten.KeyArrowRight),
	}
	g.emu.SetInput(input)

	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	if g.emu.SwapBuffers() {
		fb := g.emu.Framebuffer()
		g.img.WritePixels(fb)
	}

	op := &ebiten.DrawImageOptions{}
	op.GeoM.Scale(scale, scale)
	screen.DrawImage(g.img, op)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (int, int) {
	return 160 * scale, 144 * scale
}

func main() {
	if len(os.Args) < 2 {
		log.Fatal("Usage: gameboy_emulator <rom_file>")
	}

	emu, err := emulator.New(os.Args[1])
	if err != nil {
		log.Fatalf("Failed to initialize emulator: %v", err)
	}
	defer emu.Close()

	if err := emu.Start(); err != nil {
		log.Fatalf("Failed to start emulator: %v", err)
	}

	game := &Game{
		emu: emu,
		img: ebiten.NewImage(160, 144),
	}

	ebiten.SetWindowSize(160*scale, 144*scale)
	ebiten.SetWindowTitle("GameBoy Emulator")
	ebiten.SetWindowResizingMode(ebiten.WindowResizingModeEnabled)

	if err := ebiten.RunGame(game); err != nil {
		log.Fatal(err)
	}
}
