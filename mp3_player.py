import tkinter as tk
from tkinter import filedialog
from tkinter import ttk

from pydub import AudioSegment, effects
from pydub.playback import _play_with_simpleaudio


class MP3Player:
    def __init__(self, root):
        self.root = root
        self.root.title("Cool MP3 Player")

        self.audio = None
        self.play_obj = None
        self.loop = tk.BooleanVar()
        self.skip_silence = tk.BooleanVar()

        controls = tk.Frame(root)
        controls.pack(padx=10, pady=10)

        tk.Button(controls, text="Open", command=self.open_file).grid(row=0, column=0)
        self.play_button = tk.Button(controls, text="Play", command=self.play)
        self.play_button.grid(row=0, column=1)
        tk.Checkbutton(controls, text="Loop", variable=self.loop).grid(row=0, column=2)
        tk.Checkbutton(controls, text="Skip Silence", variable=self.skip_silence).grid(row=0, column=3)

        tk.Label(controls, text="Speed:").grid(row=1, column=0)
        self.speed = tk.DoubleVar(value=1.0)
        self.speed_slider = ttk.Scale(controls, from_=0.5, to=2.0, variable=self.speed, orient="horizontal")
        self.speed_slider.grid(row=1, column=1, columnspan=3, sticky="we")

    def open_file(self):
        path = filedialog.askopenfilename(filetypes=[("MP3 files", "*.mp3")])
        if path:
            self.audio = AudioSegment.from_mp3(path)
            self.play_button.config(state="normal")

    def process_audio(self):
        audio = self.audio
        if self.skip_silence.get():
            segments = effects.split_on_silence(audio, silence_thresh=-50, min_silence_len=500)
            audio = sum(segments)
        if self.speed.get() != 1.0:
            audio = audio._spawn(audio.raw_data, overrides={"frame_rate": int(audio.frame_rate * self.speed.get())})
            audio = audio.set_frame_rate(self.audio.frame_rate)
        return audio

    def play(self):
        if self.audio is None:
            return
        if self.play_obj is not None:
            self.play_obj.stop()
        audio = self.process_audio()
        self.play_obj = _play_with_simpleaudio(audio)
        if self.loop.get():
            self.play_obj.wait_done()
            self.play()


def main():
    root = tk.Tk()
    MP3Player(root)
    root.mainloop()


if __name__ == "__main__":
    main()
