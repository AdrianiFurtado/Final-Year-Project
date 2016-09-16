import java.awt.Color;
import javax.swing.table.DefaultTableModel;
import javax.swing.border.TitledBorder;
import java.awt.*;
import javax.swing.*;
import java.io.*;

public class Emulator{

	public static void main(String[] args){

		new GUI();

	}
}

class GUI extends JFrame{

	GUI(){
		GridLayout grid = new GridLayout(0,3);
		GridBagConstraints c = new GridBagConstraints();
		JPanel mainPanel = new JPanel(new GridBagLayout());
		setLayout(new GridLayout(1,1));
		add(mainPanel);

		//Top section of the GUI
		JPanel topPanel = new JPanel(new GridBagLayout());
		JPanel leftPanel = new JPanel();
		JPanel logoPanel = new JPanel();
		JPanel rightPanel = new JPanel(new GridLayout(2,6));

		DefaultTableModel model = new DefaultTableModel(0, 3);
		
		//Top left section of GUI
		JTable table = new JTable(model);
		table.setShowHorizontalLines(true);
		table.setShowVerticalLines(true);
		table.setGridColor(Color.BLACK);
			
		//Read from file into JTable
		String line;
		BufferedReader reader;
		try{       
			reader = new BufferedReader(new FileReader("data.txt"));
			while((line = reader.readLine()) != null) {

				model.addRow(line.split(" ")); 
			}
				reader.close();
		
		}catch(IOException e){
			
			JOptionPane.showMessageDialog(null, "Error");
			e.printStackTrace();

		}//*******************


		c.gridx = 0;
		c.gridy = 0;
		c.weightx = 1;
		c.weighty = 1;
		c.insets = new Insets(0,10,0,10);
		c.fill = GridBagConstraints.BOTH;
		TitledBorder jobT = new TitledBorder("Job Pool");
		leftPanel.add(table);
		leftPanel.setOpaque(true);
		leftPanel.setBorder(jobT);
		topPanel.add(leftPanel,c);
		//add Border and JTable to panel

		//Creating positioning and adding components  to the frame
		JLabel label = new JLabel("Program run time");
		logoPanel.add(label);
		c.gridx = 1;
		c.gridy = 0;
		c.weightx = 0.5;
		c.insets = new Insets(10,0,0,10);
		c.fill = GridBagConstraints.BOTH;
		topPanel.add(logoPanel,c);


		JLabel pNames = new JLabel("P1");
		JLabel pNames2 = new JLabel("P2");
		JProgressBar progressBar = new JProgressBar(0, 100);
		progressBar.setValue(0);
		progressBar.setStringPainted(true);
		JProgressBar progressBar2 = new JProgressBar(0, 100);
		progressBar2.setValue(0);
		progressBar2.setStringPainted(true);
		TitledBorder progressT = new TitledBorder("Progress");
		rightPanel.setBorder(progressT);
		
		c.gridx = 2;
		c.gridy = 0;
		c.weighty = 0;
		c.weightx = 0;
		c.insets = new Insets(10,0,0,10);
		c.fill = GridBagConstraints.BOTH;
		rightPanel.add(pNames);
		
		c.gridx = 3;
		rightPanel.add(progressBar);
		rightPanel.add(pNames2);
		rightPanel.add(progressBar2);

		c.gridx = 3;
		c.gridy = 0;
		c.weighty = 1;
		c.weightx = 1;
		c.insets = new Insets(0,0,0,0);
		c.fill = GridBagConstraints.BOTH;
		
		topPanel.add(rightPanel,c);
		c.gridx = 0;
		mainPanel.add(topPanel, c);
		//******************

		//Bottom section of GUI
		JTextArea gantChart = new JTextArea(3,3);
		c.gridx = 0;
		c.gridy = 1;
		c.insets = new Insets(30,10,10,10);
		c.weighty = 0;
		mainPanel.add(gantChart,c);
		guiPack();
		
		//Create and run progress bars 
		JFrame frame = new JFrame();
		for(int i = 0; i <=100; i++){
			try{
				progressBar.setValue(i);
				Thread.sleep(100);
				
				if(i == 50){
				
					for(int j = 0; j<=100 ; j++){

						progressBar2.setValue(j);
						Thread.sleep(50);
					}
				}	
					
			}catch(Exception e){}
		}
		//***********
	}

	//Method show frame
	private void guiPack(){
		
		setTitle("Realtime Scheduler");
		ImageIcon img = new ImageIcon("~/University/pic.jpeg");
		setIconImage(img.getImage());
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(800,400);
		setResizable(false);
		setLocation(250,250);
		setVisible(true);

	}
	//**************
}
