use super::super::{
    utilities::prelude::*,
    ray::Ray,
    aabb::AABB,
    hittable::prelude::*,
    material::prelude::*,
};

/// XY Axis-Aligned Rectangle
#[derive(Clone)]
pub struct XYAARectangle {
    pub x0       : f64,
    pub x1       : f64,
    pub y0       : f64,
    pub y1       : f64,
    pub z        : f64,
    pub material : Rc<dyn Material>,
}

impl XYAARectangle {
    pub fn new(x0: f64, x1: f64, y0: f64, y1: f64, z: f64, material: Rc<dyn Material>) -> Self {
        Self { x0, x1, y0, y1, z, material }
    }
}

impl Hittable for XYAARectangle {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let t = (self.z - ray.origin.z) / ray.direction.z;
        if t_min <= t && t <= t_max {
            let p = ray.at(t);
            if self.x0 <= p.x && p.x <= self.x1 && self.y0 <= p.y && p.y <= self.y1 {
                return Some(HitRecord::new(
                    p,
                    Vec3::new(0.0, 0.0, 1.0),
                    t,
                    (p.x - self.x0) / (self.x1 - self.x0),
                    (p.y - self.y0) / (self.y1 - self.y0),
                    self.material.clone(),
                    ray,
                ));
            }
        }
        None
    }

    fn bounding_box(&self, _: f64, _: f64) -> Option<AABB> {
        Some(AABB::new(
            P3d::new(self.x0, self.y0, self.z - EPS),
            P3d::new(self.x1, self.y1, self.z + EPS),
        ))
    }

    fn pdf_value(&self, origin: P3d, direction: Vec3) -> f64 {
        if let Some(rec) = self.hit(&Ray::new(origin, direction, 0.0), EPS, INFINITY) {
            let area = (self.x1 - self.x0) * (self.y1 - self.y0);
            let distance_squared = rec.t.powi(2) * direction.length2();
            let cosine = (direction.dot(rec.normal) / direction.length()).abs();

            distance_squared / (cosine * area)
        } else {
            0.0
        }
    }

    fn random(&self, origin: P3d, rng: &mut SmallRng) -> Vec3 {
        P3d::new(
            rng.gen_range(self.x0, self.x1),
            rng.gen_range(self.y0, self.y1),
            self.z,
        ) - origin
    }
}

/// YZ Axis-Aligned Rectangle
#[derive(Clone)]
pub struct YZAARectangle {
    pub y0       : f64,
    pub y1       : f64,
    pub z0       : f64,
    pub z1       : f64,
    pub x        : f64,
    pub material : Rc<dyn Material>,
}

impl YZAARectangle {
    pub fn new(y0: f64, y1: f64, z0: f64, z1: f64, x: f64, material: Rc<dyn Material>) -> Self {
        Self { y0, y1, z0, z1, x, material }
    }
}

impl Hittable for YZAARectangle {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let t = (self.x - ray.origin.x) / ray.direction.x;
        if t_min <= t && t <= t_max {
            let p = ray.at(t);
            if self.y0 <= p.y && p.y <= self.y1 && self.z0 <= p.z && p.z <= self.z1 {
                return Some(HitRecord::new(
                    p,
                    Vec3::new(1.0, 0.0, 0.0),
                    t,
                    (p.y - self.y0) / (self.y1 - self.y0),
                    (p.z - self.z0) / (self.z1 - self.z0),
                    self.material.clone(),
                    ray,
                ));
            }
        }
        None
    }

    fn bounding_box(&self, _: f64, _: f64) -> Option<AABB> {
        Some(AABB::new(
            P3d::new(self.x - EPS, self.y0, self.z0),
            P3d::new(self.x + EPS, self.y1, self.z1),
        ))
    }

    fn pdf_value(&self, origin: P3d, direction: Vec3) -> f64 {
        if let Some(rec) = self.hit(&Ray::new(origin, direction, 0.0), EPS, INFINITY) {
            let area = (self.y1 - self.y0) * (self.z1 - self.z0);
            let distance_squared = rec.t.powi(2) * direction.length2();
            let cosine = (direction.dot(rec.normal) / direction.length()).abs();

            distance_squared / (cosine * area)
        } else {
            0.0
        }
    }

    fn random(&self, origin: P3d, rng: &mut SmallRng) -> Vec3 {
        P3d::new(
            self.x,
            rng.gen_range(self.y0, self.y1),
            rng.gen_range(self.z0, self.z1),
        ) - origin
    }
}

/// ZX Axis-Aligned Rectangle
#[derive(Clone)]
pub struct ZXAARectangle {
    pub z0       : f64,
    pub z1       : f64,
    pub x0       : f64,
    pub x1       : f64,
    pub y        : f64,
    pub material : Rc<dyn Material>,
}

impl ZXAARectangle {
    pub fn new(z0: f64, z1: f64, x0: f64, x1: f64, y: f64, material: Rc<dyn Material>) -> Self {
        Self { z0, z1, x0, x1, y, material }
    }
}

impl Hittable for ZXAARectangle {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let t = (self.y - ray.origin.y) / ray.direction.y;
        if t_min <= t && t <= t_max {
            let p = ray.at(t);
            if self.z0 <= p.z && p.z <= self.z1 && self.x0 <= p.x && p.x <= self.x1 {
                return Some(HitRecord::new(
                    p,
                    Vec3::new(0.0, 1.0, 0.0),
                    t,
                    (p.z - self.z0) / (self.z1 - self.z0),
                    (p.x - self.x0) / (self.x1 - self.x0),
                    self.material.clone(),
                    ray,
                ));
            }
        }
        None
    }

    fn bounding_box(&self, _: f64, _: f64) -> Option<AABB> {
        Some(AABB::new(
            P3d::new( self.x0, self.y - EPS, self.z0),
            P3d::new( self.x1, self.y + EPS, self.z1),
        ))
    }

    fn pdf_value(&self, origin: P3d, direction: Vec3) -> f64 {
        if let Some(rec) = self.hit(&Ray::new(origin, direction, 0.0), EPS, INFINITY) {
            let area = (self.z1 - self.z0) * (self.x1 - self.x0);
            let distance_squared = rec.t.powi(2) * direction.length2();
            let cosine = (direction.dot(rec.normal) / direction.length()).abs();

            distance_squared / (cosine * area)
        } else {
            0.0
        }
    }

    fn random(&self, origin: P3d, rng: &mut SmallRng) -> Vec3 {
        P3d::new(
            rng.gen_range(self.x0, self.x1),
            self.y,
            rng.gen_range(self.z0, self.z1),
        ) - origin
    }
}
