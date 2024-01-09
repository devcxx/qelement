#include "el_slider.h"
#include <QCommonStyle>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QToolTip>

#define QT_MATERIAL_SLIDER_MARGIN 30

EL_BEGIN_NAMESPACE

OverlayWidget::OverlayWidget(QWidget* parent)
    : QWidget(parent)
{
    if (parent) {
        parent->installEventFilter(this);
    }
}

OverlayWidget::~OverlayWidget()
{
}

bool OverlayWidget::event(QEvent* event)
{
    if (!parent()) {
        return QWidget::event(event);
    }
    switch (event->type()) {
    case QEvent::ParentChange: {
        parent()->installEventFilter(this);
        setGeometry(overlayGeometry());
        break;
    }
    case QEvent::ParentAboutToChange: {
        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

bool OverlayWidget::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
    case QEvent::Move:
    case QEvent::Resize:
        setGeometry(overlayGeometry());
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

QRect OverlayWidget::overlayGeometry() const
{
    QWidget* widget = parentWidget();
    if (!widget) {
        return QRect();
    }
    return widget->rect();
}

SliderThumb::SliderThumb(Slider* slider)
    : OverlayWidget(slider->parentWidget())
    , _slider(slider)
    , _diameter(16)
    , _borderWidth(2)
    , _offset(0)
{
    slider->installEventFilter(this);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

SliderThumb::~SliderThumb()
{
}

void SliderThumb::setDiameter(qreal diameter)
{
    _diameter = diameter;
    update();
}

qreal SliderThumb::diameter() const
{
    return _diameter;
}

void SliderThumb::setBorderWidth(qreal width)
{
    _borderWidth = width;
    update();
}

qreal SliderThumb::borderWidth() const
{
    return _borderWidth;
}

void SliderThumb::setBorderColor(const QColor& color)
{
    _borderColor = color;
    update();
}

QColor SliderThumb::borderColor() const
{
    return _borderColor;
}

void SliderThumb::setFillColor(const QColor& color)
{
    _fillColor = color;
    update();
}

QColor SliderThumb::fillColor() const
{
    return _fillColor;
}

void SliderThumb::setHaloSize(qreal size)
{
    _haloSize = size;
    update();
}

qreal SliderThumb::haloSize() const
{
    return _haloSize;
}

void SliderThumb::setHaloColor(const QColor& color)
{
    _haloColor = color;
    update();
}

QColor SliderThumb::haloColor() const
{
    return _haloColor;
}

void SliderThumb::setOffset(int offset)
{
    _offset = offset;
    update();
}

int SliderThumb::offset() const
{
    return _offset;
}

bool SliderThumb::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(_slider->parentWidget());
    }

    return QWidget::eventFilter(obj, event);
}

void SliderThumb::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Halo

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_haloColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPointF disp = Qt::Horizontal == _slider->orientation()
        ? QPointF(QT_MATERIAL_SLIDER_MARGIN + _offset, _slider->height() / 2)
        : QPointF(_slider->width() / 2, QT_MATERIAL_SLIDER_MARGIN + _offset);

    QRectF halo((_slider->pos() - QPointF(_haloSize, _haloSize) / 2) + disp,
        QSizeF(_haloSize, _haloSize));

    painter.setOpacity(0.15);
    painter.drawEllipse(halo);

    // Knob

    const bool isMin = _slider->value() == _slider->minimum();

    brush.setColor(_slider->isEnabled()
            ? _fillColor
            : _slider->disabledColor());
    painter.setBrush(!_slider->isEnabled() && isMin
            ? Qt::NoBrush
            : brush);

    if (_slider->isEnabled() || isMin) {
        QPen pen;
        pen.setColor(_borderColor);
        pen.setWidthF((isMin && !_slider->isEnabled()) ? 1.7 : _borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(Qt::NoPen);
    }

    QRectF geometry = Qt::Horizontal == _slider->orientation()
        ? QRectF(_offset, _slider->height() / 2 - QT_MATERIAL_SLIDER_MARGIN,
            QT_MATERIAL_SLIDER_MARGIN * 2, QT_MATERIAL_SLIDER_MARGIN * 2)
              .translated(_slider->pos())
        : QRectF(_slider->width() / 2 - QT_MATERIAL_SLIDER_MARGIN, _offset,
            QT_MATERIAL_SLIDER_MARGIN * 2, QT_MATERIAL_SLIDER_MARGIN * 2)
              .translated(_slider->pos());

    qreal s = _slider->isEnabled() ? _diameter : 7;

    QRectF thumb(0, 0, s, s);

    thumb.moveCenter(geometry.center());

    painter.setOpacity(1);
    painter.drawEllipse(thumb);
}

// SliderTrack
SliderTrack::SliderTrack(SliderThumb* thumb, Slider* slider)
    : OverlayWidget(slider->parentWidget())
    , _slider(slider)
    , _thumb(thumb)
{
    slider->installEventFilter(this);

    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(update()));
}

SliderTrack::~SliderTrack()
{
}

void SliderTrack::setFillColor(const QColor& color)
{
    _fillColor = color;
    update();
}

QColor SliderTrack::fillColor() const
{
    return _fillColor;
}

void SliderTrack::setTrackWidth(int width)
{
    _trackWidth = width;
    update();
}

int SliderTrack::trackWidth() const
{
    return _trackWidth;
}

bool SliderTrack::eventFilter(QObject* obj, QEvent* event)
{
    if (QEvent::ParentChange == event->type()) {
        setParent(_slider->parentWidget());
    }

    return QWidget::eventFilter(obj, event);
}

void SliderTrack::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(_slider->isEnabled() ? _slider->thumbColor()
                                     : _slider->disabledColor());
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(_slider->isEnabled() ? _fillColor
                                     : _slider->disabledColor());

    qreal offset = _thumb->offset();

    if (Qt::Horizontal == _slider->orientation()) {
        painter.translate(_slider->x() + QT_MATERIAL_SLIDER_MARGIN,
            _slider->y() + _slider->height() / 2
                - static_cast<qreal>(_trackWidth) / 2);
    } else {
        painter.translate(_slider->x() + _slider->width() / 2
                - static_cast<qreal>(_trackWidth) / 2,
            _slider->y() + QT_MATERIAL_SLIDER_MARGIN);
    }

    QRectF geometry = Qt::Horizontal == _slider->orientation()
        ? QRectF(0, 0, _slider->width() - QT_MATERIAL_SLIDER_MARGIN * 2, _trackWidth)
        : QRectF(0, 0, _trackWidth, _slider->height() - QT_MATERIAL_SLIDER_MARGIN * 2);

    QRectF bgRect;
    QRectF fgRect;

    if (Qt::Horizontal == _slider->orientation()) {
        fgRect = QRectF(0, 0, offset, _trackWidth);
        bgRect = QRectF(offset, 0, _slider->width(), _trackWidth).intersected(geometry);
    } else {
        fgRect = QRectF(0, 0, _trackWidth, offset);
        bgRect = QRectF(0, offset, _trackWidth, _slider->height()).intersected(geometry);
    }

    if (!_slider->isEnabled()) {
        fgRect = fgRect.width() < 9 ? QRectF() : fgRect.adjusted(0, 0, -6, 0);
        bgRect = bgRect.width() < 9 ? QRectF() : bgRect.adjusted(6, 0, 0, 0);
    }

    if (_slider->invertedAppearance()) {
        qSwap(bgRect, fgRect);
    }

    painter.fillRect(bgRect, bg);
    painter.fillRect(fgRect, fg);
}

// Slider
Slider::Slider(QWidget* parent)
    : QAbstractSlider(parent)
    , _thumbColor(0x409eff)
    , _trackColor(0xe4e7ed)
    , _disabledColor(0xc0c4cc)
{
    init();
}

void Slider::setThumbColor(const QColor& color)
{
    _thumbColor = color;
    update();
}

QColor Slider::thumbColor() const
{
    return _thumbColor;
}

void Slider::setTrackColor(const QColor& color)
{
    _trackColor = color;
    update();
}

void Slider::setDisabledColor(const QColor& color)
{
    _disabledColor = color;
    update();
}

QColor Slider::disabledColor() const
{
    return _disabledColor;
}

void Slider::setPageStepMode(bool pageStep)
{
    _pageStepMode = pageStep;
}

bool Slider::pageStepMode() const
{
    return _pageStepMode;
}

QSize Slider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
        ? QSize(130, 34)
        : QSize(34, 130);
}

void Slider::setInvertedAppearance(bool value)
{
    QAbstractSlider::setInvertedAppearance(value);

    updateThumbOffset();
}

void Slider::sliderChange(SliderChange change)
{
    if (SliderOrientationChange == change) {
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (orientation() == Qt::Vertical) {
            sp.transpose();
        }
        setSizePolicy(sp);
    } else if (SliderValueChange == change) {
        if (minimum() == value()) {
            triggerAction(SliderToMinimum);
            // d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SliderChangedToMinimum));
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == _oldValue) {
            // d->stateMachine->postEvent(new QtMaterialStateTransitionEvent(SliderChangedFromMinimum));
        }
        _oldValue = value();
    }

    updateThumbOffset();

    QAbstractSlider::sliderChange(change);
}

void Slider::mouseMoveEvent(QMouseEvent* event)
{
    if (isSliderDown()) {
        setSliderPosition(valueFromPosition(event->pos()));
    } else {
        QRectF track(trackBoundingRect().adjusted(-2, -2, 2, 2));

        if (track.contains(event->pos()) != _hoverTrack) {
            _hoverTrack = !_hoverTrack;
            update();
        }

        QRectF thumb(0, 0, 16, 16);
        thumb.moveCenter(thumbBoundingRect().center());

        if (thumb.contains(event->pos()) != _hoverThumb) {
            _hoverThumb = !_hoverThumb;
            // QPoint point = mapToGlobal(event->pos());
            // QToolTip::showText(point, QString::number(value()));
            update();
        }

        setHovered(_hoverTrack || _hoverThumb);
    }

    QAbstractSlider::mouseMoveEvent(event);
}

void Slider::mousePressEvent(QMouseEvent* event)
{
    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(thumbBoundingRect().center());

    if (thumb.contains(pos)) {
        setSliderDown(true);
        return;
    }

    if (!_pageStepMode) {
        setSliderPosition(valueFromPosition(event->pos()));
        _thumb->setHaloSize(0);
        setSliderDown(true);
        return;
    }

    _step = true;
    _stepTo = valueFromPosition(pos);

    SliderAction action = _stepTo > sliderPosition()
        ? SliderPageStepAdd
        : SliderPageStepSub;

    triggerAction(action);
    setRepeatAction(action, 400, 8);
}

void Slider::mouseReleaseEvent(QMouseEvent* event)
{
    if (isSliderDown()) {
        setSliderDown(false);
    } else if (_step) {
        _step = false;
        setRepeatAction(SliderNoAction, 0);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}

void Slider::leaveEvent(QEvent* event)
{
    if (_hoverTrack) {
        _hoverTrack = false;
        update();
    }
    if (_hoverThumb) {
        _hoverThumb = false;
        update();
    }

    setHovered(false);

    QAbstractSlider::leaveEvent(event);
}

void Slider::updateThumbOffset()
{
    const int offset = QCommonStyle::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - QT_MATERIAL_SLIDER_MARGIN * 2
            : height() - QT_MATERIAL_SLIDER_MARGIN * 2,
        invertedAppearance());

    _thumb->setOffset(offset);
}

void Slider::init()
{
    _thumb = new SliderThumb(this);
    _track = new SliderTrack(_thumb, this);
    _stepTo = 0;
    _oldValue = value();
    _trackWidth = 6;
    _track->setTrackWidth(_trackWidth);

    _hoverTrack = false;
    _hoverThumb = false;
    _hover = false;
    _step = false;
    _pageStepMode = true;

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setPageStep(1);

    setCursor(Qt::PointingHandCursor);

    QSizePolicy sp(QSizePolicy::Expanding,
        QSizePolicy::Fixed);
    if (orientation() == Qt::Vertical) {
        sp.transpose();
    }

    setSizePolicy(sp);
    setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    _track->setFillColor(_trackColor);
    QColor holeColor = palette().color(QPalette::Base);
    if (parentWidget()) {
        holeColor = parentWidget()->palette().color(backgroundRole());
    }
    _thumb->setFillColor(holeColor);
    _thumb->setHaloColor(_trackColor);
    _thumb->setBorderColor(_thumbColor);
}

QRectF Slider::trackBoundingRect() const
{
    qreal hw = static_cast<qreal>(_trackWidth) / 2;

    return Qt::Horizontal == orientation()
        ? QRectF(QT_MATERIAL_SLIDER_MARGIN, height() / 2 - hw,
            width() - QT_MATERIAL_SLIDER_MARGIN * 2, hw * 2)
        : QRectF(width() / 2 - hw, QT_MATERIAL_SLIDER_MARGIN, hw * 2,
            height() - QT_MATERIAL_SLIDER_MARGIN * 2);
}

QRectF Slider::thumbBoundingRect() const
{
    return Qt::Horizontal == orientation()
        ? QRectF(_thumb->offset(), height() / 2 - QT_MATERIAL_SLIDER_MARGIN,
            QT_MATERIAL_SLIDER_MARGIN * 2, QT_MATERIAL_SLIDER_MARGIN * 2)
        : QRectF(width() / 2 - QT_MATERIAL_SLIDER_MARGIN, _thumb->offset(),
            QT_MATERIAL_SLIDER_MARGIN * 2, QT_MATERIAL_SLIDER_MARGIN * 2);
}

int Slider::valueFromPosition(const QPoint& pos) const
{
    const int position = Qt::Horizontal == orientation() ? pos.x() : pos.y();

    const int span = Qt::Horizontal == orientation()
        ? width() - QT_MATERIAL_SLIDER_MARGIN * 2
        : height() - QT_MATERIAL_SLIDER_MARGIN * 2;

    return QCommonStyle::sliderValueFromPosition(
        minimum(),
        maximum(),
        position - QT_MATERIAL_SLIDER_MARGIN,
        span,
        invertedAppearance());
}

void Slider::setHovered(bool status)
{
    if (_hover == status) {
        return;
    }
    _hover = status;
    update();
}

EL_END_NAMESPACE
