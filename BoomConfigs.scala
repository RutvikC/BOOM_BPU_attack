package chipyard

import freechips.rocketchip.config.{Config}

// ---------------------
// BOOM Configs
// ---------------------

class SmallBoomConfigPrefetcherEnable extends Config(
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class SmallBoomConfig extends Config(
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class MediumBoomConfig extends Config(
  new boom.common.WithNMediumBooms(1) ++                         // medium boom config
  new chipyard.config.AbstractConfig)

class LargeBoomConfig extends Config(
  new boom.common.WithNLargeBooms(1) ++                          // large boom config
  new chipyard.config.AbstractConfig)

class MegaBoomConfig extends Config(
  new boom.common.WithNMegaBooms(1) ++                           // mega boom config
  new chipyard.config.AbstractConfig)

class DualSmallBoomConfig extends Config(
  new boom.common.WithNSmallBooms(2) ++                          // 2 boom cores
  new chipyard.config.AbstractConfig)

class HwachaLargeBoomConfig extends Config(
  new chipyard.config.WithHwachaTest ++
  new hwacha.DefaultHwachaConfig ++                              // use Hwacha vector accelerator
  new boom.common.WithNLargeBooms(1) ++
  new chipyard.config.AbstractConfig)

class LoopbackNICLargeBoomConfig extends Config(
  new chipyard.harness.WithLoopbackNIC ++                        // drive NIC IOs with loopback
  new icenet.WithIceNIC ++                                       // build a NIC
  new boom.common.WithNLargeBooms(1) ++
  new chipyard.config.AbstractConfig)

class DromajoBoomConfig extends Config(
  new chipyard.harness.WithSimDromajoBridge ++                   // attach Dromajo
  new chipyard.config.WithTraceIO ++                             // enable the traceio
  new boom.common.WithNSmallBooms(1) ++
  new chipyard.config.AbstractConfig)

class SmallBoomConfigSWBPD extends Config(
  new boom.common.WithSWBPD ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class SmallBoomConfigTAGELBPD extends Config(
  new boom.common.WithTAGELBPD ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class SmallBoomConfigAlphaBPD extends Config(
  new boom.common.WithAlpha21264BPD ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class SmallBoomConfigBoom2BPD extends Config(
  new boom.common.WithBoom2BPD ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class SmallBoomConfigNLP0 extends Config(
  new boom.common.WithNLP0 ++
  new boom.common.WithNSmallBooms(1) ++                          // small BOOM with NLP0
  new chipyard.config.AbstractConfig)

class SmallBoomConfigNLP1 extends Config(
  new boom.common.WithNLP1 ++
  new boom.common.WithNSmallBooms(1) ++                          // Small BOOM with NLP1
  new chipyard.config.AbstractConfig)

class SmallBoomConfigTAGEBPD0 extends Config(
  new boom.common.WithTAGEBPD0 ++
  new boom.common.WithNSmallBooms(1) ++                          // small BOOM with TAGEBPD0
  new chipyard.config.AbstractConfig)

class SmallBoomConfigTAGEBPD1 extends Config(
  new boom.common.WithTAGEBPD1 ++
  new boom.common.WithNSmallBooms(1) ++                          // small BOOM with TAGEBPD1
  new chipyard.config.AbstractConfig)
  
class SmallBoomConfigTAGEBPD2 extends Config(
  new boom.common.WithTAGEBPD2 ++
  new boom.common.WithNSmallBooms(1) ++                          // small BOOM with TAGEBPD2
  new chipyard.config.AbstractConfig)

class SmallBoomConfigLBPD0 extends Config(
  new boom.common.WithLBPD0 ++
  new boom.common.WithNSmallBooms(1) ++                          // small BOOM with LBPD0
  new chipyard.config.AbstractConfig)

class SmallBoomConfigLBPD1 extends Config(
  new boom.common.WithLBPD1 ++
  new boom.common.WithNSmallBooms(1) ++                          // Small BOOM with LBPD1
  new chipyard.config.AbstractConfig)

class SmallBoomConfigLBPD2 extends Config(
  new boom.common.WithLBPD2 ++
  new boom.common.WithNSmallBooms(1) ++                          // Small BOOM with LBPD1
  new chipyard.config.AbstractConfig)