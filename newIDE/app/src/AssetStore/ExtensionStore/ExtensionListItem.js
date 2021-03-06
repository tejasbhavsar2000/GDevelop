// @flow
import * as React from 'react';
import { type ExtensionShortHeader } from '../../Utils/GDevelopServices/Extension';
import ButtonBase from '@material-ui/core/ButtonBase';
import Text from '../../UI/Text';
import { Trans } from '@lingui/macro';
import { Column, Line } from '../../UI/Grid';
import { ExtensionIcon } from './ExtensionIcon';

const styles = {
  iconBackground: {
    flex: 0,
    display: 'flex',
    justifyContent: 'center',
  },
  icon: {
    width: 40,
    height: 40,
    background: 'linear-gradient(45deg, #FFFFFF33, #FFFFFF)',
    padding: 4,
    borderRadius: 4,
  },
  container: {
    display: 'flex',
    textAlign: 'left',
    overflow: 'hidden',
    padding: 8,
  },
};

type Props = {|
  project: gdProject,
  extensionShortHeader: ExtensionShortHeader,
  onChoose: () => void,
  onHeightComputed: number => void,
|};

export const ExtensionListItem = ({
  project,
  extensionShortHeader,
  onChoose,
  onHeightComputed,
}: Props) => {
  const alreadyInstalled = project.hasEventsFunctionsExtensionNamed(
    extensionShortHeader.name
  );

  // Report the height of the item once it's known.
  const containerRef = React.useRef<?HTMLDivElement>(null);
  React.useLayoutEffect(() => {
    if (containerRef.current)
      onHeightComputed(containerRef.current.getBoundingClientRect().height);
  });

  return (
    <ButtonBase onClick={onChoose} focusRipple>
      <div style={styles.container} ref={containerRef}>
        <Line noMargin>
          <ExtensionIcon
            extensionShortHeader={extensionShortHeader}
            size={40}
          />
          <Column expand>
            <Text noMargin>
              {extensionShortHeader.fullName}{' '}
              {alreadyInstalled && <Trans> (already installed)</Trans>}
            </Text>
            <Text noMargin size="body2">
              {extensionShortHeader.shortDescription}
            </Text>
          </Column>
        </Line>
      </div>
    </ButtonBase>
  );
};
