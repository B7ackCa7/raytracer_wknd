#ifndef IMPACTABLE_LIST_H
#define IMPACTABLE_LIST_H


#include <vector>


class impactable_list : public impactable {
  public:
    std::vector<shared_ptr<impactable>> objects;

    impactable_list() {}
    impactable_list(shared_ptr<impactable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<impactable> object) {
        objects.push_back(object);
    }


    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};



#endif
