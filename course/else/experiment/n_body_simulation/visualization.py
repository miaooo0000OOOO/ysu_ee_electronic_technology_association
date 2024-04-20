import matplotlib.pyplot as plt
import matplotlib.animation as ani
import numpy as np

L = 20


class Star:
    def __init__(self, p: np.ndarray, v: np.ndarray, m: float) -> None:
        self.p = p
        self.v = v
        self.m = m


def read_star(s: str):
    """
    example data:
    p:(1.035389287810285, -4.901790172641149)
    v:(0.302600562390144, -0.952831808007547)
    m:1.000000
    """
    pl, vl, ml = s.splitlines()
    pl, vl, ml = pl.split(":")[1], vl.split(":")[1], ml.split(":")[1]
    pl = pl[1:-1]
    vl = vl[1:-1]
    px, py = map(float, pl.split(","))
    vx, vy = map(float, vl.split(","))
    m = float(ml)
    return Star(
        np.array([px, py], dtype=np.float64),
        np.array([vx, vy], dtype=np.float64),
        m,
    )


def read_time_frame(s: str):
    """
    example data:
    time:0.000000
    n:2
    G:1.000000
    stars:
    p:(2.684111372347487, -4.218476755990827)
    v:(-0.787772725185849, 0.615966016475958)
    m:1.000000
    p:(1.032363282186383, -4.892261854561074)
    v:(0.299680463722956, -0.954039632123736)
    m:1.000000
    stars end
    """
    lines = s.splitlines()
    time_line, n_line, G_line, stars_line = lines[0], lines[1], lines[2], lines[4:-1]
    time = float(time_line.split(":")[1])
    n = int(n_line.split(":")[1])
    G = float(G_line.split(":")[1])
    stars_groups = [
        "\n".join(stars_line[i : i + 3]) for i in range(0, len(stars_line), 3)
    ]
    stars = list(map(read_star, stars_groups))
    return (time, n, G, stars)  # Env


def read_data(s: str):
    time_frames = list(filter(lambda it: it != "", s.split("--------\n")))
    frames = []
    for time_frame in time_frames:
        frames.append(read_time_frame(time_frame))
    return frames


def display_frame(frame):
    time, n, G, stars = frame
    time: float
    n: int
    G: float
    stars: list[Star]
    ps = [[s.p[0], s.p[1]] for s in stars]
    x, y = [list(p) for p in zip(*ps)]
    plt.clf()
    plt.xlim(-L, L)
    plt.ylim(-L, L)
    plt.scatter(x, y)
    plt.pause(0.1)
    print(time)


with open("data.txt", "r") as f:
    t = f.read()
frames = read_data(t)
for frame in frames:
    display_frame(frame)
