#include <memory>

#include <dlib/image_processing/shape_predictor.h>

#include <dlib-glib/shape-predictor.hpp>

G_BEGIN_DECLS

/**
 * SECTION: shape-predictor
 * @title: ShapePredictor class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBShapePredictor is a shape_predictor class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::shape_predictor> shape_predictor;
} GDLIBShapePredictorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBShapePredictor, gdlib_shape_predictor, G_TYPE_OBJECT)

#define GDLIB_SHAPE_PREDICTOR_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                              \
                               GDLIB_TYPE_SHAPE_PREDICTOR,         \
                               GDLIBShapePredictorPrivate))

enum {
  PROP_0,
  PROP_SHAPE_PREDICTOR
};

static void
gdlib_shape_predictor_finalize(GObject *object)
{
  auto priv = GDLIB_SHAPE_PREDICTOR_GET_PRIVATE(object);

  priv->shape_predictor = nullptr;

  G_OBJECT_CLASS(gdlib_shape_predictor_parent_class)->finalize(object);
}

static void
gdlib_shape_predictor_set_property(GObject *object,
                                   guint prop_id,
                                   const GValue *value,
                                   GParamSpec *pspec)
{
  auto priv = GDLIB_SHAPE_PREDICTOR_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_SHAPE_PREDICTOR:
    priv->shape_predictor =
      *static_cast<std::shared_ptr<dlib::shape_predictor> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_shape_predictor_init(GDLIBShapePredictor *object)
{
}

static void
gdlib_shape_predictor_class_init(GDLIBShapePredictorClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_shape_predictor_finalize;
  gobject_class->set_property = gdlib_shape_predictor_set_property;

  spec = g_param_spec_pointer("shape_predictor",
                              "ShapePredictor",
                              "The raw std::shared_ptr<dlib::shape_predictor> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_SHAPE_PREDICTOR, spec);
}

/**
 * gdlib_shape_predictor_new:
 *
 * Returns: A newly read #GDLIBShapePredictor.
 *
 * Since: 1.0.0
 */
GDLIBShapePredictor *
gdlib_shape_predictor_new(void)
{
  auto shape_predictor = std::make_shared<dlib::shape_predictor>();
  return gdlib_shape_predictor_new_raw(&shape_predictor);
}

G_END_DECLS

GDLIBShapePredictor *
gdlib_shape_predictor_new_raw(std::shared_ptr<dlib::shape_predictor> *dlib_shape_predictor)
{
  auto shape_predictor = g_object_new(GDLIB_TYPE_SHAPE_PREDICTOR,
                                      "shape_predictor", dlib_shape_predictor,
                                      NULL);
  return GDLIB_SHAPE_PREDICTOR(shape_predictor);
}

std::shared_ptr<dlib::shape_predictor>
gdlib_shape_predictor_get_raw(GDLIBShapePredictor *shape_predictor)
{
  auto priv = GDLIB_SHAPE_PREDICTOR_GET_PRIVATE(shape_predictor);
  return priv->shape_predictor;
}
