use crate::utilities::prelude::*;
use crate::texture::prelude::*;
use rand::seq::SliceRandom;

#[derive(Debug, Clone)]
pub struct NoiseTexture {
    pub noise: Perlin,
    pub scale: f64,
    pub rng  : RefCell<SmallRng>,
}

impl NoiseTexture {
    pub fn new(scale: f64) -> Self {
        let mut rng = SmallRng::from_entropy();
        Self {
            noise: Perlin::new(&mut rng),
            scale,
            rng: RefCell::new(rng),
        }
    }
}

impl Texture for NoiseTexture {
    fn value(&self, _: f64, _: f64, p: P3d) -> RGB {
        RGB::new(1.0, 1.0, 1.0) * 0.5 * (1.0 + (self.scale * p.z + 10.0 * self.noise.turbulence(p)).sin())
    }
}


const POINT_COUNT: usize = 256;

#[derive(Debug, Clone)]
pub struct Perlin {
    pub px     : [usize; POINT_COUNT],
    pub py     : [usize; POINT_COUNT],
    pub pz     : [usize; POINT_COUNT],
    pub random : [Vec3;  POINT_COUNT],
}

impl Perlin {
    pub fn new(rng: &mut SmallRng) -> Self {
        let mut new = Self {
            px     : [0; POINT_COUNT],
            py     : [0; POINT_COUNT],
            pz     : [0; POINT_COUNT],
            random : [Vec3::default(); POINT_COUNT],
        };
        for i in 0..POINT_COUNT {
            new.px[i] = i;
            new.py[i] = i;
            new.pz[i] = i;
            new.random[i] = Vec3::random(-1.0, 1.0, rng);
        }
        new.px.shuffle(rng);
        new.py.shuffle(rng);
        new.pz.shuffle(rng);
        new
    }

    pub fn trilinear_interpolation(c: [[[f64; 2]; 2]; 2], u: f64, v: f64, w: f64) -> f64 {
        let mut accum = 0.0;
        for i in 0..2 {
            for j in 0..2 {
                for k in 0..2 {
                    accum += (i as f64 * u + (1 - i) as f64 * (1.0 - u))
                           * (j as f64 * v + (1 - j) as f64 * (1.0 - v))
                           * (k as f64 * w + (1 - k) as f64 * (1.0 - w))
                           * c[i][j][k];
                }
            }
        }
        accum
    }

    pub fn perlin_interpolation(c: [[[Vec3; 2]; 2]; 2], u: f64, v: f64, w: f64) -> f64 {
        let u = u * u * (3.0 - 2.0 * u);
        let v = v * v * (3.0 - 2.0 * v);
        let w = w * w * (3.0 - 2.0 * w);

        let mut accum = 0.0;
        for i in 0..2 {
            for j in 0..2 {
                for k in 0..2 {
                    accum += (i as f64 * u + (1 - i) as f64 * (1.0 - u))
                           * (j as f64 * v + (1 - j) as f64 * (1.0 - v))
                           * (k as f64 * w + (1 - k) as f64 * (1.0 - w))
                           * c[i][j][k].dot(Vec3::new(u - i as f64, v - j as f64, w - k as f64));
                }
            }
        }
        accum
    }

    pub fn noise(&self, p: P3d) -> f64 {
        let u = p.x - p.x.floor();
        let v = p.y - p.y.floor();
        let w = p.z - p.z.floor();

        let i = p.x.floor() as usize;
        let j = p.y.floor() as usize;
        let k = p.z.floor() as usize;

        let mut c = [[[Vec3::default(); 2]; 2]; 2];

        for di in 0..2 {
            for dj in 0..2 {
                for dk in 0..2 {
                    c[di][dj][dk] = self.random[
                        self.px[(i + di) & 255]
                      ^ self.py[(j + dj) & 255]
                      ^ self.pz[(k + dk) & 255]
                    ]
                }
            }
        }

        Self::perlin_interpolation(c, u, v, w)
    }

    pub fn turbulence(&self, p: P3d) -> f64 {
        let mut accum = 0.0;
        let mut tmp_p = p;
        let mut weight = 1.0;

        for _ in 0..7 {
            accum += weight * self.noise(tmp_p);
            weight *= 0.5;
            tmp_p *= 2.0;
        }

        accum.abs()
    }
}
